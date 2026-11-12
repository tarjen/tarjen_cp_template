"""Build the offline two-pane viewer. Run with --open to launch it."""
from __future__ import annotations

import argparse
from datetime import datetime, timezone
from difflib import SequenceMatcher
import json
from pathlib import Path
import webbrowser

ROOT = Path(__file__).resolve().parents[1]
CATEGORIES = {
    'data_structure': '数据结构', 'string': '字符串', 'graph': '图论',
    'math': '数学', 'geometry': '计算几何', 'others': '杂项', 'prepare': '赛前准备',
}


def align_lines(left: list[str], right: list[str]) -> list[list]:
    """Rows contain original line numbers, with None for alignment spacers."""
    rows = []
    for tag, a, b, c, d in SequenceMatcher(None, left, right, autojunk=False).get_opcodes():
        for offset in range(max(b - a, d - c)):
            rows.append([
                a + offset + 1 if a + offset < b else None,
                c + offset + 1 if c + offset < d else None,
                tag,
            ])
    return rows


def active_lines(lines: list[str]) -> int:
    return sum(bool(line.strip()) and not line.lstrip().startswith('//') for line in lines)


def build_data(root: Path = ROOT) -> dict:
    directories = [root / 'src', root / 'src-acm']
    paths = sorted({p.relative_to(directory).as_posix()
                    for directory in directories for p in directory.rglob('*.cpp')})
    templates = []
    for relative in paths:
        texts = [(directory / relative).read_text(encoding='utf-8-sig')
                 if (directory / relative).is_file() else None for directory in directories]
        lines = [text.splitlines() if text is not None else [] for text in texts]
        templates.append({
            'path': relative,
            'name': Path(relative).name,
            'category': CATEGORIES.get(relative.split('/')[0], relative.split('/')[0]),
            'full': texts[0], 'copy': texts[1],
            'active': [active_lines(part) for part in lines],
            'rows': align_lines(*lines),
        })
    return {'generatedAt': datetime.now(timezone.utc).isoformat(), 'templates': templates}


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--open', action='store_true', help='Open the viewer in the default browser')
    args = parser.parse_args()
    target = ROOT / 'viewer' / 'templates.js'
    data = build_data()
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_text('window.TEMPLATE_DATA = ' + json.dumps(data, ensure_ascii=False,
                      separators=(',', ':')) + ';\n', encoding='utf-8')
    print(f'Built {len(data["templates"])} template pairs: {target}')
    if args.open:
        webbrowser.open((target.parent / 'index.html').as_uri())


if __name__ == '__main__':
    main()
