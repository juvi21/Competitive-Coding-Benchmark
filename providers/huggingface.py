import re
from transformers import pipeline
from providers.base import BaseProvider
from utils.logger import Logger

class HuggingFaceProvider(BaseProvider):
    def __init__(self, model: str, base_prompt: str, logger: Logger):
        super().__init__(logger)
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
            f"\nProvide the solution in a markdown cpp block.\n"
        )

        response = self.generator(prompt, max_length=1500, num_return_sequences=1)
        raw_solution = response[0]['generated_text'].strip()
        self.logger.log('info', f"Generated raw solution: {raw_solution}")

        # Extract the C++ code from the markdown block
        cpp_code_match = re.search(r"```cpp(.*?)```", raw_solution, re.DOTALL)
        if cpp_code_match:
            cpp_code = cpp_code_match.group(1).strip()
            self.logger.log('info', f"Extracted C++ solution: {cpp_code}")
            return cpp_code
        else:
            self.logger.log('error', "Failed to extract C++ code from the solution")
            return ""
