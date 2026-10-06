"""Run: python tests/run_template_refactor.py [--sanitize]. Builds outside the repo."""
from pathlib import Path
import argparse
import os
import subprocess
import tempfile

parser = argparse.ArgumentParser()
parser.add_argument('--sanitize', action='store_true')
args = parser.parse_args()
source = Path(__file__).with_name('template_refactor.cpp').resolve()
with tempfile.TemporaryDirectory(prefix='cp-template-check-') as directory:
    executable = Path(directory) / ('check.exe' if os.name == 'nt' else 'check')
    flags = ['-std=c++17', '-O1', '-g', '-Wall', '-Wextra', '-D_GLIBCXX_DEBUG']
    if args.sanitize:
        flags += ['-fsanitize=address,undefined', '-fno-omit-frame-pointer']
    for test_source in [source, source.with_name('template_refactor_third.cpp'), source.with_name('template_indexing.cpp'), source.with_name('template_dynamic_diameter.cpp')]:
        subprocess.run(['g++', *flags, str(test_source), '-o', str(executable)], check=True)
        subprocess.run([str(executable)], check=True)
        if test_source == source:
            total = 0
            for tree in range(6):
                cases = list(range(15 if tree < 2 else 9)) + [15]
                if tree < 2:
                    cases += [16, 17]
                for case in cases:
                    result = subprocess.run([str(executable), str(tree), str(case)],
                                            capture_output=True, cwd=directory)
                    if result.returncode == 0 or b'Assertion' not in result.stderr:
                        raise RuntimeError(f'assert missing: tree={tree}, case={case}, stderr={result.stderr!r}')
                    total += 1
            print(f'PASS: {total} invalid segment-tree inputs rejected by assert', flush=True)
