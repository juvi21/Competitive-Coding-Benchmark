from mistralai.client import MistralClient
from mistralai.models.chat_completion import ChatMessage
from providers.base import BaseProvider
from utils.logger import Logger

class MistralProvider(BaseProvider):
    def __init__(self, api_key: str, model: str, base_prompt: str, logger: Logger, language: str):
        super().__init__(logger, language)
        self.client = MistralClient(api_key=api_key)
        self.model = model
        self.base_prompt = base_prompt

    def generate_solution(self, problem: dict) -> str:
        self.logger.log('info', f"Generating solution using Mistral model {self.model}")

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
            ChatMessage(role="user", content=prompt)
        ]

        response = self.client.chat(
            model=self.model,
            messages=messages
        )
        
        raw_solution = response.choices[0].message.content.strip()
        self.logger.log('info', f"Generated raw solution: {raw_solution}")

        return self.extract_code(raw_solution)
