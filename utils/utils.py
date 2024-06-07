import re

def sanitize_filename(name: str) -> str:
    sanitized = re.sub(r'[^a-zA-Z0-9_-]', '', name)
    return sanitized
