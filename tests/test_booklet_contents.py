"""Keep the hand-copy booklet complete and ordered like the full booklet."""
from pathlib import Path
import re
import unittest

ROOT = Path(__file__).resolve().parents[1]


class BookletContentsTests(unittest.TestCase):
    def test_handcopy_contains_every_source_tool_and_note_in_order(self):
        full = (ROOT / 'main-copy.typ').read_text(encoding='utf-8-sig')
        handcopy = (ROOT / 'main-acm.typ').read_text(encoding='utf-8-sig')
        pattern = r'^#(?:import_code\(|include\s+)"([^"]+)"'
        full_paths = re.findall(pattern, full, re.M)
        handcopy_paths = re.findall(pattern, handcopy, re.M)
        expected = [path.replace('src/', 'src-acm/', 1)
                    if path.startswith('src/') and path.endswith('.cpp') else path
                    for path in full_paths]
        self.assertTrue(full_paths)
        self.assertEqual(handcopy_paths, expected)
        printed_cpp = {path for path in handcopy_paths if path.endswith('.cpp')}
        all_cpp = {path.relative_to(ROOT).as_posix()
                   for path in (ROOT / 'src-acm').rglob('*.cpp')}
        self.assertEqual(printed_cpp, all_cpp)
        for path in handcopy_paths:
            self.assertTrue((ROOT / path).is_file(), path)


if __name__ == '__main__':
    unittest.main()
