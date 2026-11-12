"""Build the hand-copy variants; original src/ remains the complete library."""
from pathlib import Path
import re

ROOT = Path(__file__).resolve().parents[1]

# The existing legacy kth routine is known to index outside its basis array.
OMITTED = {'线性基.cpp': {'Kth_Max'}}

FIXED_VALUE_CLASSES = {
    'SegmentTree': 'll', 'DynamicTreeDiameter': 'll', 'CartesianTree': 'll',
    'LeftistHeap': 'll', 'point': 'point_t', 'line': 'point_t',
    'segment': 'point_t', 'polygon': 'point_t', 'convex': 'point_t',
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

def matching_bracket(text, start, opening, closing):
    depth = 1
    end = start + 1
    while depth and end < len(text):
        depth += (text[end] == opening) - (text[end] == closing)
        end += 1
    if depth:
        raise ValueError('Unclosed bracket in template declaration')
    return end

def erase_fixed_type_arguments(text):
    """Update code and usage examples for the concrete class APIs."""
    pattern = r'\b(' + '|'.join(FIXED_VALUE_CLASSES) + r')\s*<'
    spans = []
    literal_pattern = r'//[^\n]*|/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\''
    literals = [(part.start(), part.end()) for part in re.finditer(literal_pattern, text)
                if part.group().startswith(('"', "'"))]
    covered_until = 0
    for match in re.finditer(pattern, text):
        if match.start() < covered_until or any(start <= match.start() < end for start, end in literals):
            continue
        start = text.find('<', match.start(), match.end())
        try:
            end = matching_bracket(text, start, '<', '>')
        except ValueError:
            continue
        spans.append((match.start(), end, match.group(1)))
        covered_until = end
    for start, end, replacement in reversed(spans):
        text = text[:start] + replacement + text[end:]
    return text

def fix_value_templates(text):
    hidden = mask(text)
    edits = []
    concrete = set()
    for match in re.finditer(r'\btemplate\s*<', hidden):
        end = matching_bracket(hidden, hidden.find('<', match.start(), match.end()), '<', '>')
        declaration = re.match(r'\s*(?:struct|class)\s+(\w+)', hidden[end:])
        if not declaration or declaration.group(1) not in FIXED_VALUE_CLASSES:
            continue
        name = declaration.group(1)
        concrete.add(name)
        body_start = hidden.find('{', end + declaration.end())
        body_end = matching_bracket(hidden, body_start, '{', '}')
        while end < len(text) and text[end].isspace():
            end += 1
        edits.append((match.start(), end, ''))
        replacements = {'T': FIXED_VALUE_CLASSES[name]}
        if name == 'LeftistHeap':
            replacements['Compare'] = 'less<ll>'
        for value in re.finditer(r'\b(?:T|Compare)\b', hidden[body_start:body_end]):
            if value.group() in replacements:
                edits.append((body_start + value.start(), body_start + value.end(), replacements[value.group()]))
    for start, end, replacement in sorted(edits, reverse=True):
        text = text[:start] + replacement + text[end:]
    if 'LeftistHeap' in concrete:
        text = text.replace('using namespace std;\n', 'using namespace std;\n\ntypedef long long ll;\n', 1)
        text = text.replace('// int minimum = hp.top(x);', '// ll minimum = hp.top(x);')
        text = text.replace('默认小根，大根用 LeftistHeap<int, greater<int>>。',
                            '默认小根，大根可把 less<ll> 改为 greater<ll>。')
    if 'CartesianTree' in concrete:
        text = text.replace('类型由 a 推导。', '值类型为 ll。')
    if 'point' in concrete:
        text = text.replace('// point<T> 可指定类型；Point 是 point<point_t> 的别名。',
                            '// Point 与 point 表示同一类型，坐标类型统一使用 point_t。')
    return erase_fixed_type_arguments(text)

def handcopy_source(original, name):
    text = remove_functions(compact_calls(fix_value_templates(original)), OMITTED.get(name, set()))
    # Remove modifiers only from code, preserving every explanatory comment.
    for match in reversed(list(re.finditer(r'\b(?:explicit|inline)[ \t]+', mask(text)))):
        text = text[:match.start()] + text[match.end():]
    if name == '线性基.cpp':
        text = text.replace('    // 旧接口存在越界且未规约，请勿使用；不在当前测试支持范围内。\n', '')
    return text.rstrip('\n') + '\n'

def remove_functions(text, names):
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
        text = text[:start] + text[end:]
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
        '保留算法、类封装、原有接口、断言以及下标和返回值约定；源码不添加版本提示，也不注释停用正常接口。\n'
        '常用结构体的数值类型固定为 ll，几何坐标沿用 point_t；vector 保持动态存储。函数回调和编译期长度模板保持原实现。\n'
        '完整保留源码中的用法示例与说明注释；相邻同类调用在 110 列内合并排版，保留原有分号和调用顺序。\n'
        '没有可安全删减接口的短模板保持核心实现，不为压行数改算法。reserve 保留，防止节点池引用失效。\n'
        '完整版本已修复 Hash 的 array 初始化、重复初始化及线性基 clear 状态重置；手抄版同步这些修复。已知有误的线性基旧 Kth_Max 不收入手抄版。\n\n'
        '| 文件 | 原有效代码行 | 手抄有效代码行 |\n| --- | ---: | ---: |\n' + '\n'.join(rows) + '\n', encoding='utf-8')
    print(f'Generated {len(rows)} C++ variants')

if __name__ == '__main__':
    build()
