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
        self.assertEqual(original, generated)

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
        self.assertIn('\nFoo() {}\nassert(ready);\n', generated)

    def test_interfaces_remain_callable_without_generated_labels(self):
        original = ('// int p = tr.min_right(0, 4); // 返回位置。\n'
                    'struct SegmentTree {\n    int min_right(int i) { return i; }\n};\n')
        generated = ACM.handcopy_source(original, 'SegmentTree.cpp')
        self.assertIn('// int p = tr.min_right(0, 4); // 返回位置。', generated)
        self.assertIn('    int min_right(int i) { return i; }', generated)
        self.assertNotIn('//?', generated)
        self.assertNotIn('手抄版：', generated)
        self.assertNotIn('可选接口：', generated)
        self.assertNotIn('按需启用：', generated)

    def test_known_broken_legacy_kth_is_omitted(self):
        original = 'struct LinearBasis {\n    int Kth_Max(int k) { return a[k]; }\n    int queryMax() { return 0; }\n};\n'
        generated = ACM.handcopy_source(original, '线性基.cpp')
        self.assertNotIn('Kth_Max', generated)
        self.assertIn('int queryMax()', generated)

    def test_numeric_class_is_concrete_and_vector_remains_dynamic(self):
        original = ('// SegmentTree<> tr(vector<ll>{1, 2});\n'
                    'typedef long long ll;\ntemplate <class T = ll>\nstruct SegmentTree {\n'
                    '    vector<T> values;\n    T get() { return T(0); }\n};\n')
        generated = ACM.handcopy_source(original, 'SegmentTree.cpp')
        self.assertNotIn('template', generated)
        self.assertIn('vector<ll> values;', generated)
        self.assertIn('ll get() { return ll(0); }', generated)
        self.assertIn('// SegmentTree tr(vector<ll>{1, 2});', generated)

    def test_geometry_uses_existing_coordinate_type(self):
        original = ('template <typename T>\nstruct point { T x, y; };\n'
                    'using Point = point<point_t>;\n')
        generated = ACM.handcopy_source(original, '点与向量.cpp')
        self.assertNotIn('template', generated)
        self.assertIn('struct point { point_t x, y; };', generated)
        self.assertIn('using Point = point;', generated)

    def test_type_names_inside_strings_are_not_rewritten(self):
        original = 'const char* text = "SegmentTree<int> and point<T>";\n'
        self.assertEqual(ACM.handcopy_source(original, 'example.cpp'), original)


if __name__ == '__main__':
    unittest.main()
