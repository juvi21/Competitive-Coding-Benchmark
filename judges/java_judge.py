import subprocess
from typing import List, Dict
from utils.logger import Logger
from utils.models import Problem
from judges.base import BaseJudge
from utils.resource_tracker import ResourceTracker
import re
import os

class JavaJudge(BaseJudge):
    def __init__(self, logger: Logger):
        super().__init__(logger, "java")

    def compile_code(self, source_path: str, output_binary: str) -> bool:
        self.logger.log('info', f"Compiling {source_path}")
        compile_command = ["javac", source_path]
        result = subprocess.run(compile_command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if result.returncode == 0:
            self.logger.log('info', "Compilation successful")
            return True
        else:
            self.logger.log('error', f"Compilation failed: {result.stderr.decode()}")
            return False

    def run_code(self, class_name: str, input_data: str, time_limit: int, memory_limit: int, ignore_time_limits: bool) -> Dict:
        tracker = ResourceTracker(ignore_time_limits)
        tracker.start()

        try:
            # Create a process to run the Java program
            result = subprocess.run(['java', '-cp', 'temp', class_name], input=input_data, text=True,
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
            return {"success": False, "output": "", "error": "Time limit exceeded", "time_taken": time_limit, "memory_used": tracker.memory_used}
        except MemoryError:
            return {"success": False, "output": "", "error": "Memory limit exceeded", "time_taken": 0, "memory_used": tracker.memory_used}
        except FileNotFoundError as e:
            return {"success": False, "output": "", "error": f"File not found: {e}", "time_taken": 0, "memory_used": tracker.memory_used}

    def get_class_name(self, java_code: str) -> str:
        match = re.search(r'public\s+class\s+(\w+)', java_code)
        if match:
            return match.group(1)
        else:
            raise ValueError("No public class found in the Java code")

    def judge_problem(self, problem: Problem, source_file: str, ignore_time_limits: bool) -> List[Dict]:
        class_name = self.get_class_name(open(source_file).read())
        results = []
        for test_case in problem.test_cases:
            result = self.run_code(class_name, test_case.input, problem.time_limit, problem.memory_limit, ignore_time_limits)
            
            log_message = result["error"]
            if not ignore_time_limits and (result["error"] == "Time limit exceeded" or result["error"] == "Memory limit exceeded"):
                log_message = f"Test case exceeded limits: {result['error']}"

            pass_fail = self.validate_output(result["output"], test_case.output)
            results.append({
                "input": test_case.input,
                "expected_output": test_case.output,
                "actual_output": result["output"],
                "pass": pass_fail,
                "log": log_message,
                "time_taken": result["time_taken"],
                "memory_used": result["memory_used"]
            })
        return results
