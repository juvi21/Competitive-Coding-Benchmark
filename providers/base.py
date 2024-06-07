from abc import ABC, abstractmethod
from utils.logger import Logger

class BaseProvider(ABC):
    def __init__(self, logger: Logger):
        self.logger = logger

    @abstractmethod
    def generate_solution(self, problem_statement: str) -> str:
        pass
