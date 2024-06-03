import os

def count_lines_in_cpp_and_h_files(src_dir):
    total_lines = 0
    for root, _, files in os.walk(src_dir):
        for file in files:
            if file.endswith(".cpp") or file.endswith(".h"):
                with open(os.path.join(root, file), 'r', encoding='utf-8', errors='ignore') as f:
                    total_lines += sum(1 for _ in f)
    return total_lines

src_dir = 'src'
total_lines = count_lines_in_cpp_and_h_files(src_dir)
print(f"Total number of lines in .cpp and .h files: {total_lines}")

