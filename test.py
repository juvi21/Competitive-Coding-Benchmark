import os

def gather_python_files(root_dir, folders, output_file):
    files_to_copy = []

    # Gather files from specified folders
    for folder in folders:
        folder_path = os.path.join(root_dir, folder)
        for root, _, files in os.walk(folder_path):
            for file in files:
                if file.endswith('.py'):
                    files_to_copy.append(os.path.join(root, file))

    # Add main.py from the root directory
    main_file = os.path.join(root_dir, 'main.py')
    if os.path.isfile(main_file):
        files_to_copy.append(main_file)

    # Write the contents of all files to the output file
    with open(output_file, 'w') as outfile:
        for file in files_to_copy:
            with open(file, 'r') as infile:
                outfile.write(f"# Contents of {file}\n")
                outfile.write(infile.read())
                outfile.write("\n\n")

if __name__ == "__main__":
    root_directory = '.'  # Set the root directory
    folders_to_search = ['utils', 'providers', 'judges']
    output_filename = 'all_python_files.txt'

    gather_python_files(root_directory, folders_to_search, output_filename)
    print(f"All .py files have been copied to {output_filename}")
