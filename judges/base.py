from abc import ABC, abstractmethod
from utils.logger import Logger
from utils.models import Problem
from typing import List, Dict

class BaseJudge(ABC):
    def __init__(self, logger: Logger):
        self.logger = logger

    @abstractmethod
    def compile_code(self, source_path: str, output_binary: str) -> bool:
        pass

    @abstractmethod
    def run_code(self, binary_path: str, input_data: str, time_limit: int, memory_limit: int, ignore_time_limits: bool) -> Dict:
        pass

    @abstractmethod
    def validate_output(self, actual_output: str, expected_output: str) -> bool:
        pass

    @abstractmethod
    def judge_problem(self, problem: Problem, binary_path: str, ignore_time_limits: bool) -> List[Dict]:
        pass
