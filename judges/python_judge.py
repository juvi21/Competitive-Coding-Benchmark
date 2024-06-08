from typing import List, Dict
from utils.logger import Logger
from utils.models import Problem
from judges.base import BaseJudge
from utils.resource_tracker import ResourceTracker
import subprocess

class PythonJudge(BaseJudge):
    def __init__(self, logger: Logger):
        super().__init__(logger, "py")

    def compile_code(self, source_path: str, output_binary: str) -> bool:
        return True

    def run_code(self, binary_path: str, input_data: str, time_limit: int, memory_limit: int, ignore_time_limits: bool) -> Dict:
        tracker = ResourceTracker(ignore_time_limits)
        tracker.start()

        try:
            result = subprocess.run(['python3', binary_path], input=input_data, text=True,
                                    stdout=subprocess.PIPE, stderr=subprocess.PIPE, 
                                    preexec_fn=lambda: tracker.set_limits(time_limit, memory_limit) if not ignore_time_limits else None, 
                                    timeout=None if ignore_time_limits else time_limit)
            time_taken, memory_used = tracker.stop()
            return {
                "success": True,
                "output": result.stdout,
                "error": result.stderr,
                "time_taken": time_taken,
                "memory_used": memory_used
            }
        except subprocess.TimeoutExpired:
            return {"success": False, "output": "", "error": "Time limit exceeded", "time_taken": time_limit, "memory_used": 0}
