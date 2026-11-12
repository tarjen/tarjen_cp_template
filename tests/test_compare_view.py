"""Run with: python -m unittest discover -s tests -p test_compare_view.py"""
import importlib.util
from pathlib import Path
import tempfile
import unittest

SPEC = importlib.util.spec_from_file_location(
    'build_compare_view', Path(__file__).resolve().parents[1] / 'tools/build_compare_view.py')
VIEW = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(VIEW)


class CompareViewTests(unittest.TestCase):
    def test_alignment_preserves_original_line_numbers(self):
        left = ['head', 'assert(ok);', 'run();', 'tail']
        right = ['// hand-copy', 'head', '//? assert(ok);', 'run();']
        rows = VIEW.align_lines(left, right)
        self.assertEqual([row[0] for row in rows if row[0] is not None], [1, 2, 3, 4])
        self.assertEqual([row[1] for row in rows if row[1] is not None], [1, 2, 3, 4])
        for a, b, kind in rows:
            if kind == 'equal':
                self.assertEqual(left[a - 1], right[b - 1])
        self.assertIn([None, 1, 'insert'], rows)
        self.assertIn([4, None, 'delete'], rows)

    def test_empty_sources(self):
        self.assertEqual(VIEW.align_lines([], []), [])
        self.assertEqual(VIEW.align_lines(['one'], []), [[1, None, 'delete']])

    def test_build_pairs_utf8_and_missing_counterparts(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            for folder in ['src', 'src-acm']:
                (root / folder / 'math').mkdir(parents=True)
            source = '// 用法\nint main() {}\n'
            (root / 'src/math/测试.cpp').write_text(source, encoding='utf-8-sig')
            (root / 'src-acm/math/测试.cpp').write_text('//? optional\nint main() {}\n', encoding='utf-8')
            (root / 'src-acm/math/only-copy.cpp').write_text('', encoding='utf-8')
            data = VIEW.build_data(root)
            entries = {entry['path']: entry for entry in data['templates']}
            self.assertEqual(len(entries), 2)
            self.assertEqual(entries['math/测试.cpp']['full'], source)
            self.assertEqual(entries['math/测试.cpp']['category'], '数学')
            self.assertEqual(entries['math/测试.cpp']['active'], [1, 1])
            self.assertIsNone(entries['math/only-copy.cpp']['full'])
            self.assertEqual(entries['math/only-copy.cpp']['copy'], '')


if __name__ == '__main__':
    unittest.main()
