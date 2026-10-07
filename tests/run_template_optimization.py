"""Compare proposed optimizations against committed sources, without editing them.

Run from the repository root: python tests/run_template_optimization.py
Builds in a temporary directory; prints correctness and median timings.
"""
from pathlib import Path
import argparse
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[1]
BASE = "592e414"
FILES = {
    "pst": "src/data_structure/可持久化线段树.cpp",
    "odt": "src/data_structure/珂朵莉树.cpp",
    "diam": "src/data_structure/动态树直径.cpp",
    "bit": "src/data_structure/树状数组.cpp",
    "hash": "src/string/dequehash.cpp",
    "sos": "src/others/高维前缀和.cpp",
}


def candidates():
    old = {
        k: subprocess.check_output(["git", "show", f"{BASE}:{p}"], cwd=ROOT).decode("utf-8-sig")
        for k, p in FILES.items()
    }
    new = dict(old)
    new["pst"] = old["pst"].replace("int now = nnode(xx);", "int now = xx;")
    new["pst"] = new["pst"].replace(
        "return a[x].tag + val(a[x].ls, i) + val(a[x].rs, i);",
        "int mid = (a[x].l + a[x].r) / 2;\n"
        "        return a[x].tag + val(i <= mid ? a[x].ls : a[x].rs, i);",
    )
    new["odt"] = old["odt"].replace("int x = it->second;", "int x = it->second, y = T(x);").replace("T(x)", "y")
    new["odt"] = new["odt"].replace("int x = it->second, y = y;", "int x = it->second, y = T(x);")
    new["bit"] = old["bit"].replace(
        "for (int i = 1; i <= n; i++) add(i, a[i] - (i == 1 ? 0 : a[i - 1]));",
        "for (int i = 1; i <= n; i++) {\n"
        "            ll d = a[i] - (i == 1 ? 0 : a[i - 1]);\n"
        "            tree1[i] += d, tree2[i] += (i - 1) * d;\n"
        "            int j = i + (i & -i);\n"
        "            if (j <= n) tree1[j] += tree1[i], tree2[j] += tree2[i];\n"
        "        }",
    )
    new["hash"] = old["hash"].replace(
        "for (int i = 0; i < maxn; i++) ip[i] = inv(p[i], mod);",
        "ip[0] = 1;\n    int ib = inv(base);\n"
        "    for (int i = 1; i < maxn; i++) ip[i] = mul(ip[i - 1], ib);",
    )
    new["sos"] = old["sos"][:old["sos"].index("for (int j")] + (
        "for (int k = 1; k < (1 << n); k <<= 1)\n"
        "    for (int i = 0; i < (1 << n); i += k << 1)\n"
        "        for (int j = 0; j < k; j++) f[i + k + j] += f[i + j];\n"
    )
    new["diam"] = old["diam"].replace(
        "void build(int i, int l, int r) {",
        "void build(int i, int l, int r, const vector<T>& depth = {}) {",
    ).replace(
        "if (l == r) return;\n            int mid",
        "if (l == r) {\n"
        "                T d = depth.empty() ? T(0) : depth[l];\n"
        "                a[i].res = {d, -d, -2 * d, -d, 0};\n"
        "                return;\n            }\n            int mid",
    ).replace(
        "build(i * 2, l, mid);\n            build(i * 2 + 1, mid + 1, r);",
        "build(i * 2, l, mid, depth);\n"
        "            build(i * 2 + 1, mid + 1, r, depth);\n            pushup(i);",
    ).replace(
        "tri.build(1, 1, tot);\n        for (int i = 0; i < n - 1; i++)\n"
        "            tri.update(1, L[child[i]], R[child[i]], get<2>(edges[i]));",
        "vector<T> depth(tot + 2);\n"
        "        for (int i = 0; i < n - 1; i++) {\n"
        "            int u = child[i];\n            T w = get<2>(edges[i]);\n"
        "            depth[L[u]] += w, depth[R[u] + 1] -= w;\n        }\n"
        "        for (int i = 1; i <= tot; i++) depth[i] += depth[i - 1];\n"
        "        tri.build(1, 1, tot, depth);",
    )
    return old, new


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--only', default='', help='Comma-separated benchmark groups')
    parser.add_argument('--output', type=Path, help='Write UTF-8 results')
    parser.add_argument('--current', action='store_true', help='Compare working-tree code rather than all proposed changes')
    args = parser.parse_args()
    old, new = candidates()
    if args.current:
        new = {k: (ROOT / p).read_text(encoding='utf-8-sig') for k, p in FILES.items()}
    with tempfile.TemporaryDirectory(prefix="cp-optimization-") as tmp:
        path = Path(tmp)
        header = '#include <bits/stdc++.h>\nusing namespace std;\n'
        for name in FILES:
            for kind, sources in [("old", old), ("new", new)]:
                text = sources[name]
                if name == "sos":
                    text = "void run(vector<unsigned>& f, int n) {\n" + text + "}\n"
                header += f"namespace {kind}_{name} {{\n{text}\n}}\n#undef int\n#undef sz\n"
        clone = old['pst'].replace('int now = nnode(xx);', 'int now = xx;')
        query = old['pst'].replace(
            'return a[x].tag + val(a[x].ls, i) + val(a[x].rs, i);',
            'int mid = (a[x].l + a[x].r) / 2;\n'
            '        return a[x].tag + val(i <= mid ? a[x].ls : a[x].rs, i);',
        )
        header += f'namespace clone_pst {{\n{clone}\n}}\nnamespace query_pst {{\n{query}\n}}\n'
        (path / "variants.h").write_text(header, encoding="utf-8")
        binary = path / "check.exe"
        subprocess.run([
            "g++", "-std=c++17", "-O2", "-DNDEBUG", "-Wall", "-Wextra",
            "-I", str(path), str(ROOT / "tests/template_optimization.cpp"),
            "-o", str(binary),
        ], check=True)
        if args.output:
            with args.output.open('w', encoding='utf-8') as out:
                subprocess.run([str(binary), args.only], stdout=out, check=True)
        else:
            subprocess.run([str(binary), args.only], check=True)


if __name__ == "__main__":
    main()
