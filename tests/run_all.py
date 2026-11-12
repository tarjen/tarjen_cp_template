"""Run both template directories: python tests/run_all.py [--sanitize]."""
from pathlib import Path
import argparse
import subprocess
import sys

root = Path(__file__).resolve().parents[1]
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--sanitize', action='store_true')
args = parser.parse_args()
flags = ['--sanitize'] if args.sanitize else []
print('=== Python generator tests ===', flush=True)
subprocess.run([sys.executable, '-m', 'unittest', 'discover', '-s', str(root / 'tests'),
                '-p', 'test_*.py'], cwd=root, check=True)
for name in ['run_template_refactor.py', 'run_acm_variants.py']:
    print(f'=== {name} ===', flush=True)
    subprocess.run([sys.executable, str(root / 'tests' / name), *flags],
                   cwd=root, check=True)
print('PASS: full and hand-copy template suites', flush=True)
