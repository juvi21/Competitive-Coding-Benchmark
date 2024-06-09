import re
import google.generativeai as genai
from providers.base import BaseProvider
from utils.logger import Logger

class GoogleProvider(BaseProvider):
    def __init__(self, api_key: str, model: str, base_prompt: str, logger: Logger, language: str):
        super().__init__(logger, language)
        genai.configure(api_key=api_key)
        self.client = genai.GenerativeModel(model)
        self.model = model
        self.base_prompt = base_prompt

    def generate_solution(self, problem: dict) -> str:
        self.logger.log('info', f"Generating solution using Google Gemini model {self.model}")

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

        response = self.client.generate_content(prompt)
        raw_solution = response.text.strip()
        self.logger.log('info', f"Generated raw solution: {raw_solution}")

        return self.extract_code(raw_solution)

    def extract_code(self, raw_solution: str) -> str:
        code_match = re.search(rf"```{self.language}(.*?)```", raw_solution, re.DOTALL)
        if code_match:
            code = code_match.group(1).strip()
            self.logger.log('info', f"Extracted {self.language} solution: {code}")
            return code
        else:
            self.logger.log('error', f"Failed to extract {self.language} code from the solution")
            return ""
