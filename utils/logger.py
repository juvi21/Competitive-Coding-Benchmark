import logging
import json
import os

class Logger:
    def __init__(self, name="JudgeLogger", level=logging.INFO):
        self.logger = logging.getLogger(name)
        self.logger.setLevel(level)
        handler = logging.StreamHandler()
        formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')
        handler.setFormatter(formatter)
        self.logger.addHandler(handler)

    def log(self, level, message):
        if level.lower() == 'info':
            self.logger.info(message)
        elif level.lower() == 'debug':
            self.logger.debug(message)
        elif level.lower() == 'warning':
            self.logger.warning(message)
        elif level.lower() == 'error':
            self.logger.error(message)
        elif level.lower() == 'critical':
            self.logger.critical(message)

class JSONLogger:
    def __init__(self, filename):
        self.filename = filename
        if os.path.exists(self.filename):
            with open(self.filename, 'r') as file:
                self.data = json.load(file)
        else:
            self.data = {
                "problems": [],
                "total_passed_problems": 0
            }
        os.makedirs(os.path.dirname(self.filename), exist_ok=True)

    def log_initial_config(self, config):
        self.data["initial_config"] = {
            "ignore_time_limits": config.ignore_time_limits,
            "model": config.model,
            "provider": config.provider,
            "categories": config.categories,
            "shots": config.shots
        }
        self._write_log()

    def log_problem(self, title, category, results, solution, total_problems_passed, shots_info):
        passed_count = sum(1 for result in results if result['pass'])
        total_count = len(results)
        exceeded_time_count = sum(1 for result in results if "Time limit exceeded" in result.get("error", ""))
        exceeded_memory_count = sum(1 for result in results if "Memory limit exceeded" in result.get("error", ""))

        mean_time_taken = sum(result['time_taken'] for result in results) / total_count if total_count > 0 else 0
        mean_memory_used = sum(result['memory_used'] for result in results) / total_count if total_count > 0 else 0

        problem_passed = passed_count == total_count

        problem_log = {
            "title": title,
            "category": category,
            "solution": solution,
            "passed_test_cases": passed_count,
            "total_test_cases": total_count,
            "mean_time_taken": mean_time_taken,
            "mean_memory_used": mean_memory_used,
            "failure_reasons": [result["log"] for result in results if not result["pass"]],
            "failed_test_cases": [i + 1 for i, result in enumerate(results) if not result["pass"]],
            "exceeded_time_count": exceeded_time_count,
            "exceeded_memory_count": exceeded_memory_count,
            "total_problems_passed": total_problems_passed,
            "passed": problem_passed,
            "shots_info": shots_info
        }
        self.data["problems"].append(problem_log)
        if problem_passed:
            self.data["total_passed_problems"] += 1
        self._write_log()

    def log_compilation_error(self, title, category, solution, error_message, total_problems_passed, shot):
        problem_log = {
            "title": title,
            "category": category,
            "solution": solution,
            "passed_test_cases": 0,
            "total_test_cases": 0,
            "mean_time_taken": 0,
            "mean_memory_used": 0,
            "failure_reasons": [error_message],
            "failed_test_cases": [],
            "exceeded_time_count": 0,
            "exceeded_memory_count": 0,
            "total_problems_passed": total_problems_passed,
            "passed": False,
            "shot": shot
        }
        self.data["problems"].append(problem_log)
        self._write_log()

    def _write_log(self):
        with open(self.filename, 'w') as file:
            json.dump(self.data, file, indent=4)
