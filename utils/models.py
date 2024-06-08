from pydantic import BaseModel, validator
from typing import List, Optional

class Example(BaseModel):
    input: str
    output: str

class TestCase(BaseModel):
    input: str
    output: str

class Problem(BaseModel):
    title: str
    time_limit: str
    memory_limit: str
    problem_statement: str
    input: str
    output: str
    constraints: str
    example: Example
    test_cases: List[TestCase]
    category: Optional[str] = None

    @validator('time_limit')
    def parse_time_limit(cls, v):
        if v.endswith(" s"):
            return int(float(v.replace(" s", "")))
        raise ValueError("Invalid time limit format")

    @validator('memory_limit')
    def parse_memory_limit(cls, v):
        if v.endswith(" MB"):
            return int(v.replace(" MB", ""))
        raise ValueError("Invalid memory limit format")

class Config(BaseModel):
    ignore_time_limits: bool
    provider: str
    api_key: str
    model: str
    base_prompt: str = "You are a helpful assistant."
    categories: Optional[List[str]] = None
    shots: int = 1
    continue_from_log: Optional[str] = None 
    language: str = "cpp"
