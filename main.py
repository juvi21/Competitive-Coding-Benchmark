import json
import time
import os
from tqdm import tqdm
from judges.cpp_judge import CppJudge
from utils.logger import Logger, JSONLogger
from utils.models import Problem, Config
from providers.openai import OpenAIProvider
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
    
    problems = load_problems('problems.jsonl')
    config = load_config('config.json')
    
    ignore_time_limits = config.ignore_time_limits
    
    judge = CppJudge(logger)
    
    provider = None
    if config.provider == "openai":
        provider = OpenAIProvider(config.api_key, config.model, config.base_prompt, logger)
    
    total_problems = len(problems)
    problems_passed = 0

    for index, problem_str in enumerate(tqdm(problems, desc="Processing problems")):
        problem_data = json.loads(problem_str)
        logger.log('info', f"Judging problem: {problem_data['title']}")
        
        cpp_file = f"solution_{index}.cpp"
        binary_file = f"./solution_binary_{index}"
        
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
                        logger.log('info', f"Problem {index + 1}/{total_problems}: {summary}")
                        if all(result['pass'] for result in results):
                            problems_passed += 1
                        json_logger.log_problem(problem.title, results, solution, problems_passed)
                        logger.log('info', f"Total problems passed so far: {problems_passed}/{total_problems}")
                    except ValidationError as e:
                        logger.log('error', f"Problem validation error: {e}")
                else:
                    logger.log('error', "Compilation failed")
                    json_logger.log_compilation_error(problem_data["title"], solution, "Compilation failed", problems_passed)
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
