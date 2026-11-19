"""Run the ten-line stress loop with real generator/reference/solution processes."""
from pathlib import Path
import os
import shlex
import subprocess
import sys
import tempfile
import unittest

SCRIPT = Path(__file__).resolve().parents[1] / 'src/prepare/duipai.py'


class DuipaiTests(unittest.TestCase):
    def run_case(self, candidate, reference='print(input())'):
        with tempfile.TemporaryDirectory(prefix='stress test ') as directory:
            root = Path(directory)
            source = SCRIPT.read_text(encoding='utf-8')
            self.assertEqual(len(source.splitlines()), 10)
            # Cap successful tests at two rounds; only replace executable commands.
            source = source.replace('range(1, 100001)', 'range(1, 3)')
            for name, code in [('testin', 'print(7)'), ('abiaocheng', reference),
                               ('nedtest', candidate)]:
                path = root / (name + '.py')
                path.write_text(code, encoding='utf-8')
                command = [Path(sys.executable).as_posix(), path.as_posix()]
                quoted = subprocess.list2cmdline(command) if os.name == 'nt' else shlex.join(command)
                source = source.replace("f'{p}" + name + "{s}", "f'" + quoted)
            test = root / 'stress.py'
            test.write_text(source, encoding='utf-8')
            result = subprocess.run([sys.executable, str(test)], cwd=root,
                                    capture_output=True, text=True, timeout=15)
            saved = {p.name: p.read_bytes() for p in root.glob('*.txt')}
            return result, saved

    def test_multiple_rounds_ignore_whitespace(self):
        result, _ = self.run_case("print('  ' + input() + '  ')")
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertEqual(result.stdout.splitlines(), ['1 AC', '2 AC'])

    def test_wrong_answer_stops_and_preserves_files(self):
        result, saved = self.run_case('print(int(input()) + 1)')
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(result.stdout.strip(), '1 WA')
        self.assertEqual(saved['data.txt'].strip(), b'7')
        self.assertEqual(saved['biaoda.txt'].strip(), b'7')
        self.assertEqual(saved['aatest.txt'].strip(), b'8')

    def test_program_failure_stops_before_comparison(self):
        result, _ = self.run_case('raise SystemExit(7)')
        self.assertNotEqual(result.returncode, 0)
        self.assertNotIn('AC', result.stdout)
        self.assertIn('CalledProcessError', result.stderr)

    def test_timeout_stops_and_preserves_input(self):
        result, saved = self.run_case('import time; time.sleep(5)')
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('TimeoutExpired', result.stderr)
        self.assertEqual(saved['data.txt'].strip(), b'7')


if __name__ == '__main__':
    unittest.main()
