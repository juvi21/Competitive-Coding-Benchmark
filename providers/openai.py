import openai
from providers.base import BaseProvider
from utils.logger import Logger

class OpenAIProvider(BaseProvider):
    def __init__(self, api_key: str, model: str, base_prompt: str, logger: Logger, language: str):
        super().__init__(logger, language)
        openai.api_key = api_key
        self.model = model
        self.base_prompt = base_prompt

    def generate_solution(self, problem: dict) -> str:
        self.logger.log('info', f"Generating solution using OpenAI model {self.model}")

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

        messages = [
            {"role": "system", "content": "You are a helpful assistant."},
            {"role": "user", "content": prompt}
        ]
        
        response = openai.chat.completions.create(
            model=self.model,
            messages=messages,
            temperature=0.7,
            max_tokens=1500,
            top_p=1.0,
            frequency_penalty=0.0,
            presence_penalty=0.0,
        )
        raw_solution = response.choices[0].message.content.strip()
        self.logger.log('info', f"Generated raw solution: {raw_solution}")

        return self.extract_code(raw_solution)
