"""Release benchmark of current DC3 and doubling SA; all arrays checked exactly.

python tests/run_suffix_benchmark.py [--rounds 5] [--output results.csv]
Only a temporary copy has its ST build removed for the third timing column.
"""
from pathlib import Path
import argparse
import os
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--rounds', type=int, default=5)
parser.add_argument('--output', type=Path)
args = parser.parse_args()
source = (ROOT / 'src/string/倍增sa.cpp').read_text(encoding='utf-8')
start = source.index('        st.assign(__lg(n) + 1, vector<int>(n));')
end = source.index('\n    }\n    int get(', start)
with tempfile.TemporaryDirectory(prefix='suffix-benchmark-') as directory:
    work = Path(directory)
    (work / 'suffix_without_st.h').write_text(source[:start] + source[end:], encoding='utf-8')
    executable = work / ('benchmark.exe' if os.name == 'nt' else 'benchmark')
    subprocess.run(['g++', '-std=c++17', '-O2', '-DNDEBUG', '-I', str(work),
                    str(ROOT / 'tests/suffix_benchmark.cpp'), '-o', str(executable)], check=True)
    lines = []
    with subprocess.Popen([str(executable), str(args.rounds)], stdout=subprocess.PIPE,
                          text=True) as process:
        for line in process.stdout:
            print(line, end='', flush=True)
            lines.append(line)
        if process.wait():
            raise RuntimeError('benchmark failed')
    if args.output:
        args.output.write_text(''.join(lines), encoding='utf-8')
