import re
import anthropic
from providers.base import BaseProvider
from utils.logger import Logger

class AnthropicProvider(BaseProvider):
    def __init__(self, api_key: str, model: str, base_prompt: str, logger: Logger):
        super().__init__(logger)
        self.api_key = api_key
        self.model = model
        self.base_prompt = base_prompt
        self.client = anthropic.Anthropic(api_key=api_key)

    def generate_solution(self, problem: dict) -> str:
        self.logger.log('info', f"Generating solution using Anthropic model {self.model}")

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

        response = self.client.messages.create(
            model=self.model,
            max_tokens=1500,
            temperature=0.7,
            system="You are a helpful assistant.",
            messages=[{"role": "user", "content": prompt}]
        )
        raw_solution = response['completion'].strip()
        self.logger.log('info', f"Generated raw solution: {raw_solution}")

        cpp_code_match = re.search(r"```cpp(.*?)```", raw_solution, re.DOTALL)
        if cpp_code_match:
            cpp_code = cpp_code_match.group(1).strip()
            self.logger.log('info', f"Extracted C++ solution: {cpp_code}")
            return cpp_code
        else:
            self.logger.log('error', "Failed to extract C++ code from the solution")
            return ""
