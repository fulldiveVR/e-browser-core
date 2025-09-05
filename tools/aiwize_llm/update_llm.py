#!/usr/bin/env python3
import os
import shutil
import argparse
import sys

# Path constants. (All of these should be absolute paths.)
BASE_PATH = os.path.join(
    os.path.abspath(os.path.join(os.path.dirname(__file__), "..", "..", ".."))
)


def UpdateAIWizeLLM(output_path: str, names_list: list):
    print("Start UpdateAIWizeLLM")
    out_path = os.path.normpath(os.path.join(BASE_PATH, output_path.removeprefix("//")))
    out_gen_path = os.path.normpath(
        os.path.join(BASE_PATH, "brave/tools/aiwize_llm/data")
    )

    for file in names_list:
        file_src_path = os.path.join(out_gen_path, file)
        file_out_path = os.path.join(out_path, file)
        if os.path.exists(file_out_path):
            os.remove(file_out_path)
        shutil.copy(file_src_path, file_out_path)
        os.chmod(file_out_path, 0o755)
        print(f"{file} copied.")

    return 0


def main(args):
    parser = argparse.ArgumentParser()
    parser.add_argument("--output-path", required=True)
    parser.add_argument('-n', '--names-list', nargs='+', required=True)
    options = parser.parse_args(args)

    error_code = UpdateAIWizeLLM(options.output_path, options.names_list)

    print("Finished UpdateAIWizeLLM with error-code:", error_code)
    return error_code


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
