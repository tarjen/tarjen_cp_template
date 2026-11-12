"""Build the hand-copy variants; original src/ remains the complete library."""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]

# These functions are optional as a group, including their recursive overloads.
OPTIONAL = {
    'SegmentTree.cpp': {'min_right', 'max_left'},
    'SegmentTree单点.cpp': {'min_right', 'max_left'},
    'SegmentSet.cpp': {'write'},
    'dc3.cpp': {'writ'},
    '倍增sa.cpp': {'writ'},
    'FWT.cpp': {'print'},
    '线性基.cpp': {'Insert', 'intersection', 'merge', 'queryMin', 'Kth_Max'},
}

def mask(text):
    # Preserve offsets while hiding comments and literals from brace matching.
    pattern = r'//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\''
    return re.sub(pattern, lambda m: ''.join('\n' if c == '\n' else ' ' for c in m[0]), text)

def optional_functions(text, names):
    hidden = mask(text)
    spans = []
    for name in names:
        for m in re.finditer(r'(?m)^[ \t]*(?:[\w:<>,*&]+[ \t]+)+' + re.escape(name) + r'\s*\(', hidden):
            pos = m.end() - 1
            depth = 1
            end = pos + 1
            while depth:
                depth += (hidden[end] == '(') - (hidden[end] == ')')
                end += 1
            brace = hidden.find('{', end)
            if brace < 0 or ';' in hidden[end:brace]:
                continue
            depth, end = 1, brace + 1
            while depth:
                depth += (hidden[end] == '{') - (hidden[end] == '}')
                end += 1
            spans.append((m.start(), end))
    for start, end in sorted(spans, reverse=True):
        body = text[start:end]
        text = text[:start] + '// 按需启用：以下整个函数组一起取消注释。\n' + '\n'.join('//? ' + line for line in body.splitlines()) + text[end:]
    return text

def build():
    rows = []
    for source in sorted((ROOT / 'src').rglob('*.cpp'),
                         key=lambda path: path.relative_to(ROOT / 'src').as_posix()):
        original = source.read_text(encoding='utf-8-sig')
        text = optional_functions(original, OPTIONAL.get(source.name, set()))
        # Preconditions belong in the printed reference, not in the typed body.
        # Keep these comments for the reader; the check runner can restore them.
        text = re.sub(r'(?m)^(\s*)assert\(([^\n]*)\);([^\n]*)$', r'\1//? assert(\2);\3', text)
        # Explicit/inline add no useful work for these contest snippets.
        text = re.sub(r'\b(?:explicit|inline)\s+', '', text)
        # Legacy 1-based char* convenience overloads: string is the primary API.
        text = re.sub(r'(?m)^(\s*)((?:void|int) (?:insert|query)\(const char\*[^\n]+)$', r'\1//? \2', text)
        # Do not remove reserve: a few implementations rely on stable references.
        # Keep all algorithmic guards (empty ranges, sentinels, carries, etc.).
        if source.name == '线性基.cpp':
            text = text.replace('if (t > queryMax()) return false;\n        ', '')
            # The old kth routine indexes outside a[36]; do not present it as usable.
            text = text.replace('//?     ll Kth_Max', '// 已知旧实现不正确（越界且未规约），请勿启用。\n//?     ll Kth_Max')
        # Header: retain conventions; remove executable demo lines from the print body.
        lines = text.splitlines()
        first = next((i for i, l in enumerate(lines) if l.strip() and not l.lstrip().startswith('//')), 0)
        contract = [l for l in lines[:first] if not re.match(r'//\s*(?:[A-Za-z_][\w:<>,*& ]*\s+\w+\s*[=(]|\w+\.\w+\(|for\s*\()', l)]
        text = '\n'.join(contract + lines[first:]) + '\n'
        relative = source.relative_to(ROOT / 'src')
        target = ROOT / 'src-acm' / relative
        target.parent.mkdir(parents=True, exist_ok=True)
        text = '// 手抄版：沿用原算法与类封装；//? 标记为按需抄写。\n' + text
        target.write_text(text, encoding='utf-8')
        active_before = sum(bool(l.strip()) and not l.lstrip().startswith('//') for l in original.splitlines())
        active_after = sum(bool(l.strip()) and not l.lstrip().startswith('//') for l in text.splitlines())
        rows.append(f'| `{relative.as_posix()}` | {active_before} | {active_after} |')
    (ROOT / 'ACM源码改动清单.md').write_text('# ACM 源码改动清单\n\n完整复制版在 `src/`，手抄版在 `src-acm/`，每个 cpp 一一对应。\n\n'
        '保留算法、类封装、下标和返回值约定；非必要 assert、旧 char* 入口及指定扩展函数改为 `//?` 注释。\n'
        '没有可安全删减接口的短模板保持核心实现，不为压行数改算法。reserve 保留，防止节点池引用失效。\n'
        '完整版本已修复 Hash 的 array 初始化、重复初始化及线性基 clear 状态重置；手抄版同步这些修复。线性基查询移除重复求最大值；旧 kth 接口标为不可启用。\n\n'
        '| 文件 | 原有效代码行 | 手抄有效代码行 |\n| --- | ---: | ---: |\n' + '\n'.join(rows) + '\n', encoding='utf-8')
    print(f'Generated {len(rows)} C++ variants')

if __name__ == '__main__':
    build()
