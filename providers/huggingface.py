from transformers import pipeline
from providers.base import BaseProvider
from utils.logger import Logger

class HuggingFaceProvider(BaseProvider):
    def __init__(self, model: str, base_prompt: str, logger: Logger, language: str):
        super().__init__(logger, language)
        self.model = model
        self.base_prompt = base_prompt
        self.generator = pipeline('text-generation', model=model)

    def generate_solution(self, problem: dict) -> str:
        self.logger.log('info', f"Generating solution using HuggingFace model {self.model}")

        prompt = (
            f"{self.base_prompt}\n"
            f"Problem Title: {problem['title']}\n"
            f"Problem Statement: {problem['problem_statement']}\n"
            f"Input: {problem['input']}\n"
            f"Output: {problem['output']}\n"
            f"Constraints: {problem['constraints']}\n"
            f"Example Input: {problem['example']['input']}\n"
            f"Example Output: {problem['example']['output']}\n"
            f"\nProvide the solution in a markdown {self.language} block.\n"
        )

        response = self.generator(prompt, max_length=1500, num_return_sequences=1)
        raw_solution = response[0]['generated_text'].strip()
        self.logger.log('info', f"Generated raw solution: {raw_solution}")

        return self.extract_code(raw_solution)
