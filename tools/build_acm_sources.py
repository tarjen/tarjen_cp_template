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

def compact_calls(text, width=110):
    """Put adjacent calls to the same function on one line; keep both semicolons."""
    lines = text.splitlines(keepends=True)
    hidden = mask(text).splitlines(keepends=True)
    call = re.compile(r'^([ \t]*)([A-Za-z_]\w*(?:(?:::|\.|->)[A-Za-z_]\w*)*)\([^;\n]*\);[ \t]*$')
    result = []
    index = 0
    while index < len(lines):
        if index + 1 < len(lines):
            first = call.fullmatch(hidden[index].rstrip('\r\n'))
            second = call.fullmatch(hidden[index + 1].rstrip('\r\n'))
            joined = lines[index].rstrip('\r\n').rstrip() + ' ' + lines[index + 1].lstrip(' \t')
            comments = any(mark in lines[index] + lines[index + 1] for mark in ('//', '/*'))
            if (first and second and first.group(1, 2) == second.group(1, 2)
                    and not comments and len(joined.rstrip('\r\n').expandtabs(4)) <= width):
                result.append(joined)
                index += 2
                continue
        result.append(lines[index])
        index += 1
    return ''.join(result)

def disable_code_lines(text, pattern):
    """Add //? to matching code lines without matching text inside comments."""
    for match in reversed(list(re.finditer(pattern, mask(text), re.MULTILINE))):
        start = match.start()
        while text[start] in ' \t':
            start += 1
        text = text[:start] + '//? ' + text[start:]
    return text

def handcopy_source(original, name):
    text = optional_functions(compact_calls(original), OPTIONAL.get(name, set()))
    text = disable_code_lines(text, r'^[ \t]*assert\([^\n]*\);[ \t]*$')
    # Remove modifiers only from code, preserving every explanatory comment.
    for match in reversed(list(re.finditer(r'\b(?:explicit|inline)[ \t]+', mask(text)))):
        text = text[:match.start()] + text[match.end():]
    text = disable_code_lines(text, r'^[ \t]*(?:void|int) (?:insert|query)\(const char\*[^\n]+$')
    if name == '线性基.cpp':
        text = text.replace('if (t > queryMax()) return false;\n        ', '')
        text = text.replace('//?     ll Kth_Max', '// 已知旧实现不正确（越界且未规约），请勿启用。\n//?     ll Kth_Max')
    header = '// 手抄版：保留说明与用法，适度压行；//? 为按需代码，调用可选接口前需恢复对应函数组。\n'
    if name in OPTIONAL:
        header += '// 可选接口：' + '、'.join(sorted(OPTIONAL[name])) + '。\n'
    return header + text.rstrip('\n') + '\n'

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
        text = handcopy_source(original, source.name)
        relative = source.relative_to(ROOT / 'src')
        target = ROOT / 'src-acm' / relative
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(text, encoding='utf-8')
        active_before = sum(bool(l.strip()) and not l.lstrip().startswith('//') for l in original.splitlines())
        active_after = sum(bool(l.strip()) and not l.lstrip().startswith('//') for l in text.splitlines())
        rows.append(f'| `{relative.as_posix()}` | {active_before} | {active_after} |')
    (ROOT / 'ACM源码改动清单.md').write_text('# ACM 源码改动清单\n\n完整复制版在 `src/`，手抄版在 `src-acm/`，每个 cpp 一一对应。\n\n'
        '保留算法、类封装、下标和返回值约定；非必要 assert、旧 char* 入口及指定扩展函数改为 `//?` 注释。\n'
        '完整保留源码中的用法示例与说明注释；相邻同类调用在 110 列内合并排版，保留原有分号和调用顺序。\n'
        '没有可安全删减接口的短模板保持核心实现，不为压行数改算法。reserve 保留，防止节点池引用失效。\n'
        '完整版本已修复 Hash 的 array 初始化、重复初始化及线性基 clear 状态重置；手抄版同步这些修复。线性基查询移除重复求最大值；旧 kth 接口标为不可启用。\n\n'
        '| 文件 | 原有效代码行 | 手抄有效代码行 |\n| --- | ---: | ---: |\n' + '\n'.join(rows) + '\n', encoding='utf-8')
    print(f'Generated {len(rows)} C++ variants')

if __name__ == '__main__':
    build()
