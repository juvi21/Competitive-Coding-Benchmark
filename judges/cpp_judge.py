import subprocess
import resource
from typing import List, Dict
from utils.logger import Logger
from utils.models import Problem
from judges.base import BaseJudge
import time

class CppJudge(BaseJudge):
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
        def set_limits():
            if not ignore_time_limits:
                resource.setrlimit(resource.RLIMIT_CPU, (time_limit, time_limit))
                resource.setrlimit(resource.RLIMIT_AS, (memory_limit * 1024 * 1024, memory_limit * 1024 * 1024))

        try:
            # Ensure input_data is a string
            if not isinstance(input_data, str):
                input_data = input_data.decode()

            start_time = time.time()
            result = subprocess.run([binary_path], input=input_data, text=True,
                                    stdout=subprocess.PIPE, stderr=subprocess.PIPE,
                                    preexec_fn=set_limits if not ignore_time_limits else None, timeout=None if ignore_time_limits else time_limit)
            end_time = time.time()
            memory_used = resource.getrusage(resource.RUSAGE_CHILDREN).ru_maxrss
            time_taken = end_time - start_time

            return {
                "success": True,
                "output": result.stdout,
                "error": "",
                "time_taken": time_taken,
                "memory_used": memory_used
            }
        except subprocess.TimeoutExpired:
            return {"success": False, "output": "", "error": "Time limit exceeded", "time_taken": time_limit, "memory_used": 0}
        except MemoryError:
            return {"success": False, "output": "", "error": "Memory limit exceeded", "time_taken": 0, "memory_used": memory_limit}
        except FileNotFoundError as e:
            return {"success": False, "output": "", "error": f"File not found: {e}", "time_taken": 0, "memory_used": 0}

    def validate_output(self, actual_output: str, expected_output: str) -> bool:
        return actual_output.strip() == expected_output.strip()

    def judge_problem(self, problem: Problem, binary_path: str, ignore_time_limits: bool) -> List[Dict]:
        results = []
        for test_case in problem.test_cases:
            result = self.run_code(binary_path, test_case.input, problem.time_limit, problem.memory_limit, ignore_time_limits)
            
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
