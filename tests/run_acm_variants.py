"""Test hand-copy sources directly, without rewriting any source code."""
from pathlib import Path
import argparse
import os
import shutil
import subprocess
import sys
import tempfile

root = Path(__file__).resolve().parents[1]
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--sanitize', action='store_true')
args = parser.parse_args()
flags = ['-std=c++17', '-O1', '-g', '-Wall', '-Wextra', '-D_GLIBCXX_DEBUG']
if args.sanitize:
    flags += ['-fsanitize=address,undefined', '-fno-omit-frame-pointer']
with tempfile.TemporaryDirectory(prefix='acm-variants-') as directory:
    work = Path(directory)
    shutil.copytree(root / 'tests', work / 'tests')
    shutil.copytree(root / 'src-acm', work / 'src')
    # Compile the actual hand-copy sources as printed in the viewer and PDF.
    executable = work / ('core.exe' if os.name == 'nt' else 'core')
    for name in ['template_core.cpp', 'poly_pow_n2.cpp']:
        subprocess.run(['g++', *flags, '-DACM_VARIANT', str(root / 'tests' / name),
                        '-o', str(executable)], check=True)
        subprocess.run([str(executable)], check=True)
    print('PASS: hand-copy interfaces compiled directly', flush=True)
    subprocess.run([sys.executable, str(work / 'tests/run_template_refactor.py'),
                    *(['--sanitize'] if args.sanitize else [])], check=True)
