import subprocess
from typing import List, Dict
from utils.logger import Logger
from utils.models import Problem
from judges.base import BaseJudge
from utils.resource_tracker import ResourceTracker

class CppJudge(BaseJudge):
    def __init__(self, logger: Logger):
        super().__init__(logger, "cpp")

    def compile_code(self, source_path: str, output_binary: str) -> bool:
        self.logger.log('info', f"Compiling {source_path} to {output_binary}")
        compile_command = ["g++", source_path, "-o", output_binary]
        result = subprocess.run(compile_command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if result.returncode == 0:
            self.logger.log('info', "Compilation successful")
            return True
        else:
            self.logger.log('error', f"Compilation failed: {result.stderr.decode()}")
            return False

    def run_code(self, binary_path: str, input_data: str, time_limit: int, memory_limit: int, ignore_time_limits: bool) -> Dict:
        tracker = ResourceTracker(ignore_time_limits)
        tracker.start()

        try:
            result = subprocess.run([binary_path], input=input_data, text=True,
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
            return {"success": False, "output": "", "error": "Time limit exceeded", "time_taken": time_limit, "memory_used": memory_used}
        except MemoryError:
            return {"success": False, "output": "", "error": "Memory limit exceeded", "time_taken": 0, "memory_used": memory_limit}
        except FileNotFoundError as e:
            return {"success": False, "output": "", "error": f"File not found: {e}", "time_taken": 0, "memory_used": 0}
