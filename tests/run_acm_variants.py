"""Verify ACM core and restore optional methods for the existing regression suite."""
from pathlib import Path
import os
import re
import shutil
import subprocess
import tempfile

root = Path(__file__).resolve().parents[1]
with tempfile.TemporaryDirectory(prefix='acm-variants-') as directory:
    work = Path(directory)
    shutil.copytree(root / 'tests', work / 'tests')
    shutil.copytree(root / 'src-acm', work / 'src')
    # Test the printed default, with optional methods actually disabled.
    core = work / 'core.cpp'
    includes = ['data_structure/SegmentTree.cpp', 'string/hash.cpp', 'others/线性基.cpp']
    text = '#include <bits/stdc++.h>\nusing namespace std;\nusing ll = long long;\n'
    for i, name in enumerate(includes):
        text += f'namespace t{i} {{\n#include "src/{name}"\n}}\n'
    text += '''int main() {
        t0::SegmentTree<> t(vector<ll>{1,2,3});
        t.update(0,1,4); assert(t.query(0,2)==14);
        t0::SegmentTree<> empty(0); empty.update(0,0,7); assert(empty.query(0,0)==7);
        string s="ababa"; t1::Hash h; h.Hash_init(s);
        assert(h.get1(1,3)==h.get2(1,3)); assert(h.get1(1,3)==h.get1(3,5));
        t2::LinearBasis b; b.insert(1); b.insert(2);
        assert(b.queryMax()==3 && b.query(3) && !b.query(4));
        b.insert(0); b.clear(); assert(!b.flag && b.tot==0 && b.queryMax()==0);
    }'''
    core.write_text(text, encoding='utf-8')
    executable = work / ('core.exe' if os.name == 'nt' else 'core')
    subprocess.run(['g++', '-std=c++17', '-O1', str(core), '-o', str(executable)], check=True)
    subprocess.run([str(executable)], check=True)
    print('PASS: default ACM segment tree / hash / linear basis', flush=True)
    # Re-enable optional functions and assertions to exercise their full contracts.
    for path in (work / 'src').rglob('*.cpp'):
        if path.name == '线性基.cpp':
            continue  # its legacy kth implementation is explicitly unsupported
        text = re.sub(r'(?m)^([ \t]*)//\? ?', r'\1', path.read_text(encoding='utf-8'))
        path.write_text(text, encoding='utf-8')
    subprocess.run(['python', str(work / 'tests/run_template_refactor.py')], check=True)
