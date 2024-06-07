import os
import requests
from bs4 import BeautifulSoup
import time
import zipfile
import json
from tqdm import tqdm

# Base URLs for the tasks and zip files
base_task_url = 'https://cses.fi/problemset/task/'
base_zip_url = 'https://cses.fi/problemset/tests/'

# Cookies and headers to mimic the browser behavior
cookies = {
    'PHPSESSID': '78dfdd26847d32244c766a0a7c079e55faca0df0',
}

headers = {
    'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64; rv:124.0) Gecko/20100101 Firefox/124.0',
    'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,*/*;q=0.8',
    'Accept-Language': 'en-US,en;q=0.5',
    'Content-Type': 'application/x-www-form-urlencoded',
    'Origin': 'https://cses.fi',
    'Connection': 'keep-alive',
    'Referer': 'https://cses.fi/problemset/tests/',
    'Upgrade-Insecure-Requests': '1',
    'Sec-Fetch-Dest': 'document',
    'Sec-Fetch-Mode': 'navigate',
    'Sec-Fetch-Site': 'same-origin',
    'Sec-Fetch-User': '?1',
}

# Data for the POST request to download the zip file
data = {
    'csrf_token': '43cd7e7c24de820adfcb438241cb1072',
    'download': 'true',
}

# Folder to save the problems and zip files
folder_name = 'problems'
if not os.path.exists(folder_name):
    os.makedirs(folder_name)

def extract_problem_details(html_content):
    soup = BeautifulSoup(html_content, 'html.parser')

    # Extract problem title
    title_tag = soup.find('title')
    problem_title = title_tag.text.replace("CSES - ", "").strip() if title_tag else "Task"

    # Extract constraints
    constraints = soup.find('ul', class_='task-constraints')
    time_limit = memory_limit = "Not found"
    if constraints:
        time_limit_tag = constraints.find_all('li')[0]
        memory_limit_tag = constraints.find_all('li')[1]
        time_limit = time_limit_tag.text.replace("Time limit:", "").strip() if time_limit_tag else "Not found"
        memory_limit = memory_limit_tag.text.replace("Memory limit:", "").strip() if memory_limit_tag else "Not found"

    # Extract problem statement
    content_div = soup.find('div', class_='md')
    problem_statement = content_div.text.strip() if content_div else "No problem statement found"

    # Extract input, output, constraints, and example sections
    input_section = output_section = constraints_section = "Not found"
    example_section = {"input": "Not found", "output": "Not found"}
    if content_div:
        headers = content_div.find_all('h1')
        for header in headers:
            section_id = header.get('id')
            if section_id == 'input':
                input_section = header.find_next_sibling('p').text.strip()
            elif section_id == 'output':
                output_section = header.find_next_sibling('p').text.strip()
            elif section_id == 'constraints':
                constraints_ul = header.find_next_sibling('ul')
                if constraints_ul:
                    constraints_section = constraints_ul.text.strip()
            elif section_id == 'example':
                example_input = header.find_next_sibling('pre').text.strip()
                example_output = header.find_next_sibling('pre').find_next_sibling('pre').text.strip()
                example_section = {"input": example_input, "output": example_output}

    # Transcribe inline math elements into Markdown
    problem_statement = transcribe_math(problem_statement)
    input_section = transcribe_math(input_section)
    output_section = transcribe_math(output_section)
    constraints_section = transcribe_math(constraints_section)
    example_section["input"] = transcribe_math(example_section["input"])
    example_section["output"] = transcribe_math(example_section["output"])

    problem_details = {
        "title": problem_title,
        "time_limit": time_limit,
        "memory_limit": memory_limit,
        "problem_statement": problem_statement,
        "input": input_section,
        "output": output_section,
        "constraints": constraints_section,
        "example": example_section,
        "test_cases": []
    }

    return problem_details

def transcribe_math(text):
    if text == "Not found":
        return text
    return text.replace("\\(", "$").replace("\\)", "$")

def extract_test_cases(tests_folder):
    test_cases = []
    for file in os.listdir(tests_folder):
        if file.endswith('.in'):
            test_case_number = file.split('.')[0]
            input_file = os.path.join(tests_folder, f'{test_case_number}.in')
            output_file = os.path.join(tests_folder, f'{test_case_number}.out')
            if os.path.exists(input_file) and os.path.exists(output_file):
                with open(input_file, 'r') as infile, open(output_file, 'r') as outfile:
                    test_cases.append({
                        "input": infile.read().strip(),
                        "output": outfile.read().strip()
                    })
    return test_cases

successful_html_downloads = 0
successful_zip_downloads = 0

jsonl_filename = 'problems.jsonl'
if os.path.exists(jsonl_filename):
    os.remove(jsonl_filename)

for task_id in tqdm(range(1067, 2801), desc="Processing tasks"):
    task_url = f'{base_task_url}{task_id}/'
    zip_url = f'{base_zip_url}{task_id}/'
    
    response_html = requests.get(task_url, cookies=cookies, headers=headers)

    if response_html.status_code == 200:
        problem_details = extract_problem_details(response_html.text)
        problem_title = problem_details["title"].replace(" ", "_")
        
        if problem_title != "Task":
            successful_html_downloads += 1
            
            problem_folder = os.path.join(folder_name, problem_title)
            if not os.path.exists(problem_folder):
                os.makedirs(problem_folder)
            
            html_filename = os.path.join(problem_folder, 'problem.html')
            zip_filename = os.path.join(problem_folder, 'problem.zip')
            json_filename = os.path.join(problem_folder, f'{problem_title}.json')
            tests_folder = os.path.join(problem_folder, 'tests')

            with open(html_filename, 'w', encoding='utf-8') as file:
                file.write(response_html.text)
            print(f'HTML page for task {task_id} ({problem_title}) downloaded successfully.')

            with open(json_filename, 'w', encoding='utf-8') as file:
                json.dump(problem_details, file, indent=4)
            print(f'JSON file for task {task_id} ({problem_title}) created successfully.')
        else:
            print(f'Skipped task {task_id} due to default title.')
    else:
        print(f'Failed to download HTML page for task {task_id}. Status code: {response_html.status_code}')
        continue

    response_zip = requests.post(zip_url, cookies=cookies, headers=headers, data=data)

    if response_zip.status_code == 200:
        if problem_title != "Task":
            successful_zip_downloads += 1
            with open(zip_filename, 'wb') as file:
                file.write(response_zip.content)
            print(f'Zip file for task {task_id} ({problem_title}) downloaded successfully.')
            
            if not os.path.exists(tests_folder):
                os.makedirs(tests_folder)
            try:
                with zipfile.ZipFile(zip_filename, 'r') as zip_ref:
                    zip_ref.extractall(tests_folder)
                print(f'Unzipped files for task {task_id} ({problem_title}) successfully.')
                
                problem_details["test_cases"] = extract_test_cases(tests_folder)
                
                with open(json_filename, 'w', encoding='utf-8') as file:
                    json.dump(problem_details, file, indent=4)

                with open(jsonl_filename, 'a', encoding='utf-8') as file:
                    file.write(json.dumps(problem_details) + '\n')
            except zipfile.BadZipFile:
                print(f'File {zip_filename} is not a zip file or it is corrupted.')
                os.remove(zip_filename)  
        else:
            print(f'Skipped zip download for task {task_id} due to default title.')
    else:
        print(f'Failed to download zip file for task {task_id}. Status code: {response_zip.status_code}')
    # Be kind to the server. Give it some rest 
    time.sleep(2)

print(f'Successfully downloaded {successful_html_downloads} HTML pages and {successful_zip_downloads} zip files.')
