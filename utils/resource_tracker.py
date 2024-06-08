import resource
import time

class ResourceTracker:
    def __init__(self, ignore_time_limits: bool = False):
        self.start_time = None
        self.start_memory = None
        self.ignore_time_limits = ignore_time_limits

    def start(self):
        self.start_time = time.time()
        self.start_memory = resource.getrusage(resource.RUSAGE_CHILDREN).ru_maxrss

    def stop(self):
        end_time = time.time()
        end_memory = resource.getrusage(resource.RUSAGE_CHILDREN).ru_maxrss
        time_taken = end_time - self.start_time
        memory_used = (end_memory - self.start_memory) if end_memory >= self.start_memory else end_memory
        return time_taken, memory_used

    def set_limits(self, time_limit: int, memory_limit: int):
        if not self.ignore_time_limits:
            resource.setrlimit(resource.RLIMIT_CPU, (time_limit, time_limit))
            resource.setrlimit(resource.RLIMIT_AS, (memory_limit * 1024 * 1024, memory_limit * 1024 * 1024))
