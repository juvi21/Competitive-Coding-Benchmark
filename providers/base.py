from abc import ABC, abstractmethod
from utils.logger import Logger
import re

class BaseProvider(ABC):
    def __init__(self, logger: Logger, language: str):
        self.logger = logger
        self.language = language

    @abstractmethod
    def generate_solution(self, problem_statement: str) -> str:
        pass

    def extract_code(self, raw_solution: str) -> str:
        code_block = f"```{self.language}"
        code_match = re.search(rf"{code_block}(.*?```)", raw_solution, re.DOTALL)
        if code_match:
            code = code_match.group(1).strip().strip("`")
            self.logger.log('info', f"Extracted {self.language} solution: {code}")
            return code
        else:
            self.logger.log('error', f"Failed to extract {self.language} code from the solution")
            return ""
