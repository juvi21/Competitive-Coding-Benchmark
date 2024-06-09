import anthropic
from providers.base import BaseProvider
from utils.logger import Logger

class AnthropicProvider(BaseProvider):
    def __init__(self, api_key: str, model: str, base_prompt: str, logger: Logger, language: str):
        super().__init__(logger, language)
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
            f"\nProvide the solution in a markdown {self.language} block.\n"
        )

        try:
            response = self.client.messages.create(
                model=self.model,
                max_tokens=1500,
                temperature=0.7,
                system="You are a helpful assistant.",
                messages=[{"role": "user", "content": prompt}]
            )

            raw_solution = ''.join([block.text for block in response.content]).strip() # this is a little hacky TODO
            self.logger.log('info', f"Generated raw solution: {raw_solution}")

            return self.extract_code(raw_solution)
        except anthropic.APIConnectionError as e:
            self.logger.log('error', f"Connection error: {e}")
        except anthropic.RateLimitError as e:
            self.logger.log('error', f"Rate limit error: {e}")
        except anthropic.APIStatusError as e:
            self.logger.log('error', f"API error: {e.status_code} - {e.response}")

        return None
