import json
import time
import os
from tqdm import tqdm
from judges.cpp_judge import CppJudge
from utils.logger import Logger, JSONLogger
from utils.models import Problem, Config
from providers.openai import OpenAIProvider
from utils.utils import sanitize_filename  # Import the new utility function
from pydantic import ValidationError

def load_problems(file_path: str) -> list[str]:
    problems = []
    with open(file_path, 'r') as file:
        for line in file:
            problems.append(line.strip())
    return problems

def load_config(config_path: str) -> Config:
    with open(config_path, 'r') as file:
        config_json = json.load(file)
        return Config(**config_json)

def generate_summary(results: list[dict]) -> str:
    passed_count = sum(1 for result in results if result['pass'])
    total_count = len(results)
    return f"Passed {passed_count}/{total_count} test cases"

def main():
    logger = Logger()
    json_logger = JSONLogger('log.json')
    
    problems = load_problems('sorted_problems.jsonl')
    config = load_config('config.json')
    
    ignore_time_limits = config.ignore_time_limits
    categories_filter = config.categories  # Get the categories from the config

    judge = CppJudge(logger)
    
    provider = None
    if config.provider == "openai":
        provider = OpenAIProvider(config.api_key, config.model, config.base_prompt, logger)
    
    if categories_filter:
        filtered_problems = [problem for problem in problems if json.loads(problem).get("category") in categories_filter]
    else:
        filtered_problems = problems

    total_filtered_problems = len(filtered_problems)
    problems_passed = 0

    for index, problem_str in enumerate(tqdm(filtered_problems, desc="Processing problems")):
        problem_data = json.loads(problem_str)
        problem_title = problem_data['title']
        sanitized_title = sanitize_filename(problem_title)  # Sanitize the problem title for file names
        logger.log('info', f"Judging problem: {problem_title}")

        cpp_file = f"{sanitized_title}.cpp"
        binary_file = f"./{sanitized_title}_binary"

        # Generate a solution using the provider
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
                        logger.log('info', f"Problem {index + 1}/{total_filtered_problems}: {summary}")
                        if all(result['pass'] for result in results):
                            problems_passed += 1
                        json_logger.log_problem(problem.title, problem.category or "Uncategorized", results, solution, problems_passed)
                        logger.log('info', f"Total problems passed so far: {problems_passed}/{total_filtered_problems}")
                    except ValidationError as e:
                        logger.log('error', f"Problem validation error: {e}")
                else:
                    logger.log('error', "Compilation failed")
                    json_logger.log_compilation_error(problem_data["title"], problem_data.get("category", "Uncategorized"), solution, "Compilation failed", problems_passed)
            else:
                logger.log('error', "Solution generation failed")
        else:
            logger.log('error', "No provider configured")

        # Clean up the solution and binary files after judging
        if os.path.exists(cpp_file):
            os.remove(cpp_file)
        if os.path.exists(binary_file):
            os.remove(binary_file)

if __name__ == "__main__":
    main()
