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
    for test_source in [source, source.with_name('template_refactor_third.cpp')]:
        subprocess.run(['g++', *flags, str(test_source), '-o', str(executable)], check=True)
        subprocess.run([str(executable)], check=True)
