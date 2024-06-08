from abc import ABC, abstractmethod
from utils.logger import Logger
from utils.models import Problem
from utils.resource_tracker import ResourceTracker
from typing import List, Dict
import subprocess
import resource

class BaseJudge(ABC):
    def __init__(self, logger: Logger, language_extension: str):
        self.logger = logger
        self.language_extension = language_extension

    @abstractmethod
    def compile_code(self, source_path: str, output_binary: str) -> bool:
        pass

    @abstractmethod
    def run_code(self, binary_path: str, input_data: str, time_limit: int, memory_limit: int, ignore_time_limits: bool) -> Dict:
        pass

    def validate_output(self, actual_output: str, expected_output: str) -> bool:
        return actual_output.strip() == expected_output.strip()

    def judge_problem(self, problem: Problem, binary_path: str, ignore_time_limits: bool) -> List[Dict]:
        results = []
        for test_case in problem.test_cases:
            result = self.run_code(binary_path, test_case.input, problem.time_limit, problem.memory_limit, ignore_time_limits)
            pass_fail = self.validate_output(result["output"], test_case.output)
            results.append({
                "input": test_case.input,
                "expected_output": test_case.output,
                "actual_output": result["output"],
                "pass": pass_fail,
                "log": result["error"],
                "time_taken": result["time_taken"],
                "memory_used": result["memory_used"]
            })
        return results

    def _set_limits(self, time_limit: int, memory_limit: int, ignore_time_limits: bool):
        if not ignore_time_limits:
            resource.setrlimit(resource.RLIMIT_CPU, (time_limit, time_limit))
            resource.setrlimit(resource.RLIMIT_AS, (memory_limit * 1024 * 1024, memory_limit * 1024 * 1024))
