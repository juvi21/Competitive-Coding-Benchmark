import json

# Load the JSON data
with open('benchmark/anthropic_claude-3-5-sonnet-20240620_cpp_log.json') as f:
    data = json.load(f)

# Initialize counters
total_passed = 0
category_counts = {}
category_passed_counts = {}

# Process each problem
for problem in data:
    # Count problems that passed all test cases
    if problem['passed_test_cases'] == problem['total_test_cases']:
        total_passed += 1

    # Count problems by category
    category = problem['category']
    if category not in category_counts:
        category_counts[category] = 0
        category_passed_counts[category] = 0
    category_counts[category] += 1

    # Count problems that passed all test cases by category
    if problem['passed_test_cases'] == problem['total_test_cases']:
        category_passed_counts[category] += 1

# Calculate percentages
category_percentages = {category: category_passed_counts[category] / category_counts[category] * 100 for category in category_counts}

# Print results
print(f'Total problems that passed all test cases: {total_passed}')
print(f'Problem counts by category: {category_counts}')
print(f'Problem counts that passed all test cases by category: {category_passed_counts}')
print(f'Percentage of problems that passed all test cases by category: {category_percentages}')