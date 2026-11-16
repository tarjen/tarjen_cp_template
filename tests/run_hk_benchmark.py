"""Optional local timing: release HK versus the repository Dinic on identical graphs."""
from pathlib import Path
import os
import subprocess
import tempfile

root = Path(__file__).resolve().parents[1]
with tempfile.TemporaryDirectory(prefix='hk-benchmark-') as directory:
    executable = Path(directory) / ('benchmark.exe' if os.name == 'nt' else 'benchmark')
    subprocess.run(['g++', '-std=c++17', '-O2', '-DNDEBUG',
                    str(root / 'tests/hk_benchmark.cpp'), '-o', str(executable)], check=True)
    subprocess.run([str(executable)], check=True, timeout=120)
