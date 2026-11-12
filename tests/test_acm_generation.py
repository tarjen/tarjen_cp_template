"""Protect hand-copy comments and conservative one-line formatting."""
import importlib.util
from pathlib import Path
import unittest

SPEC = importlib.util.spec_from_file_location(
    'build_acm_sources', Path(__file__).resolve().parents[1] / 'tools/build_acm_sources.py')
ACM = importlib.util.module_from_spec(SPEC)
SPEC.loader.exec_module(ACM)


class HandcopyGenerationTests(unittest.TestCase):
    def test_usage_examples_and_contract_comments_are_kept(self):
        original = ('// 用法：\n// KMP tr("aba");\n'
                    '// vector<int> p = tr.find("ababa"); // {1,3}，1base。\n'
                    'struct KMP {};\n')
        generated = ACM.handcopy_source(original, 'kmp.cpp')
        self.assertIn(original, generated)

    def test_adjacent_calls_share_a_line_but_keep_statement_boundaries(self):
        original = '        tag_union(i, i * 2);\n        tag_union(i, i * 2 + 1);\n'
        expected = '        tag_union(i, i * 2); tag_union(i, i * 2 + 1);\n'
        self.assertEqual(ACM.compact_calls(original), expected)

    def test_different_calls_comments_and_long_lines_are_not_merged(self):
        for source in [
            '    first(1);\n    second(2);\n',
            '    run(1); // 保留说明\n    run(2);\n',
            '/*\n    run(1);\n    run(2);\n*/\n',
        ]:
            with self.subTest(source=source):
                self.assertEqual(ACM.compact_calls(source), source)
        source = '    run(123456);\n    run(234567);\n'
        self.assertEqual(ACM.compact_calls(source, width=20), source)

    def test_code_like_comments_and_string_contents_are_not_rewritten(self):
        comment = ('// inline explicit 参数说明\n'
                   '/*\nassert(ready);\nvoid insert(const char* text);\n*/\n')
        original = comment + 'const char* label = "inline explicit ";\nexplicit Foo() {}\nassert(ready);\n'
        generated = ACM.handcopy_source(original, 'example.cpp')
        self.assertIn(comment, generated)
        self.assertIn('"inline explicit "', generated)
        self.assertIn('\nFoo() {}\n//? assert(ready);\n', generated)

    def test_optional_interface_examples_remain_documented(self):
        original = ('// int p = tr.min_right(0, 4); // 返回位置。\n'
                    'struct SegmentTree {\n    int min_right(int i) { return i; }\n};\n')
        generated = ACM.handcopy_source(original, 'SegmentTree.cpp')
        self.assertIn('// int p = tr.min_right(0, 4); // 返回位置。', generated)
        self.assertIn('可选接口：max_left、min_right', generated)
        self.assertIn('//?     int min_right', generated)


if __name__ == '__main__':
    unittest.main()
