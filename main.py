import json
from judges.cpp_judge import CppJudge
from utils.logger import Logger
from utils.models import Problem, Config
from providers.openai import OpenAIProvider
from pydantic import ValidationError
import os

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

def generate_report(results: list[dict]) -> str:
    report = []
    for result in results:
        report_line = (f"Input: {result['input']}\nExpected Output: {result['expected_output']}\n"
                       f"Actual Output: {result['actual_output']}\nPass: {result['pass']}\n"
                       f"{result['log']}\n")
        report.append(report_line)
    return "\n".join(report)

def main():
    logger = Logger()
    
    problems = load_problems('problems.jsonl')
    config = load_config('config.json')
    
    ignore_time_limits = config.ignore_time_limits
    
    judge = CppJudge(logger)
    
    provider = None
    if config.provider == "openai":
        provider = OpenAIProvider(config.api_key, config.model, config.base_prompt, logger)
    
    for index, problem_str in enumerate(problems):
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
                        report = generate_report(results)
                        print(report)
                    except ValidationError as e:
                        logger.log('error', f"Problem validation error: {e}")
                else:
                    logger.log('error', "Compilation failed")
            else:
                logger.log('error', "Solution generation failed")
        else:
            logger.log('error', "No provider configured")

        # Clean up the binary file after judging
        if os.path.exists(binary_file):
            os.remove(binary_file)

if __name__ == "__main__":
    main()
