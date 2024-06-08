import os
import json
from tqdm import tqdm
from pydantic import ValidationError
from datasets import load_dataset
from judges.cpp_judge import CppJudge
from utils.logger import Logger, JSONLogger
from utils.models import Problem, Config
from utils.utils import sanitize_filename
from providers.openai import OpenAIProvider
from providers.huggingface import HuggingFaceProvider
from providers.anthropic import AnthropicProvider

def load_problems_from_hf(dataset_name: str, split: str = 'train') -> list[str]:
    dataset = load_dataset(dataset_name, split=split)
    problems = [json.dumps(problem) for problem in dataset]
    return problems

def load_config(config_path: str) -> Config:
    with open(config_path, 'r') as file:
        config_json = json.load(file)
        return Config(**config_json)

def generate_summary(results: list[dict]) -> str:
    passed_count = sum(1 for result in results if result['pass'])
    total_count = len(results)
    return f"Passed {passed_count}/{total_count} test cases"

def load_existing_log(log_filename: str) -> dict:
    if os.path.exists(log_filename):
        with open(log_filename, 'r') as file:
            return json.load(file)
    return {}

def main():
    logger = Logger()
    
    config = load_config('config.json')

    # Create the benchmark and temp directories if they don't exist
    os.makedirs("benchmark", exist_ok=True)
    os.makedirs("temp", exist_ok=True)

    log_filename = os.path.join("benchmark", f"{sanitize_filename(config.provider)}_{sanitize_filename(config.model)}_log.json")
    json_logger = JSONLogger(log_filename)
    
    if not config.continue_from_log:
        json_logger.log_initial_config(config)
    
    problems = load_problems_from_hf("juvi21/cses-fi-competitive-coding-problems")
    
    ignore_time_limits = config.ignore_time_limits
    categories_filter = config.categories  
    shots = config.shots  

    judge = CppJudge(logger)
    
    provider = None
    if config.provider == "openai":
        provider = OpenAIProvider(config.api_key, config.model, config.base_prompt, logger)
    elif config.provider == "huggingface":
        provider = HuggingFaceProvider(config.model, config.base_prompt, logger)
    elif config.provider == "anthropic":
        provider = AnthropicProvider(config.api_key, config.model, config.base_prompt, logger)

    if categories_filter:
        filtered_problems = [problem for problem in problems if json.loads(problem).get("category") in categories_filter]
    else:
        filtered_problems = problems

    total_filtered_problems = len(filtered_problems)
    problems_passed = json_logger.data.get("total_passed_problems", 0)
    
    processed_titles = set(problem["title"] for problem in json_logger.data.get("problems", []))

    for index, problem_str in enumerate(tqdm(filtered_problems, desc="Processing problems")):
        problem_data = json.loads(problem_str)
        problem_title = problem_data['title']
        
        if problem_title in processed_titles:
            logger.log('info', f"Skipping already processed problem: {problem_title}")
            continue

        sanitized_title = sanitize_filename(problem_title)
        logger.log('info', f"Judging problem: {problem_title}")

        for shot in range(1, shots + 1):
            cpp_file = os.path.join("temp", f"{sanitized_title}_shot_{shot}.cpp")
            binary_file = os.path.join("temp", f"{sanitized_title}_binary_shot_{shot}")

            if provider:
                solution = provider.generate_solution(problem_data)
                if solution:
                    with open(cpp_file, 'w') as file:
                        file.write(solution)

                    if judge.compile_code(cpp_file, binary_file):
                        try:
                            problem = Problem(**problem_data)
                            results = judge.judge_problem(problem, binary_file, ignore_time_limits)
                            summary = generate_summary(results)
                            logger.log('info', f"Problem {index + 1}/{total_filtered_problems} Shot {shot}: {summary}")
                            if all(result['pass'] for result in results):
                                problems_passed += 1
                                json_logger.log_problem(problem.title, problem.category or "Uncategorized", results, solution, problems_passed, {"shot": shot, "status": "passed"})
                                break  # Exit the loop if all test cases passed
                            else:
                                json_logger.log_problem(problem.title, problem.category or "Uncategorized", results, solution, problems_passed, {"shot": shot, "status": "failed"})
                        except ValidationError as e:
                            logger.log('error', f"Problem validation error: {e}")
                    else:
                        logger.log('error', "Compilation failed")
                        json_logger.log_compilation_error(problem_data["title"], problem_data.get("category", "Uncategorized"), solution, "Compilation failed", problems_passed, shot)
                else:
                    logger.log('error', "Solution generation failed")
                    json_logger.log_compilation_error(problem_data["title"], problem_data.get("category", "Uncategorized"), "No solution generated", "Solution generation failed", problems_passed, shot)
            else:
                logger.log('error', "No provider configured")

            # Clean up the solution and binary files after judging
            if os.path.exists(cpp_file):
                os.remove(cpp_file)
            if os.path.exists(binary_file):
                os.remove(binary_file)

if __name__ == "__main__":
    main()
