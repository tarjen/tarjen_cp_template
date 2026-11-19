import os, subprocess
p, s = ('', '.exe') if os.name == 'nt' else ('./', '')
for t in range(1, 100001):
    subprocess.run(f'{p}testin{s} > data.txt', shell=True, check=True, timeout=2)
    subprocess.run(f'{p}abiaocheng{s} < data.txt > biaoda.txt', shell=True, check=True, timeout=2)
    subprocess.run(f'{p}nedtest{s} < data.txt > aatest.txt', shell=True, check=True, timeout=2)
    a = open('biaoda.txt', 'rb').read().split()
    b = open('aatest.txt', 'rb').read().split()
    print(t, 'AC' if a == b else 'WA', flush=True)
    if a != b: break
