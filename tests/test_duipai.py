"""Exercise the stress-test CLI with real generator/reference/candidate processes."""
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

SCRIPT = Path(__file__).resolve().parents[1] / 'src/prepare/duipai.py'


class DuipaiTests(unittest.TestCase):
    def run_case(self, candidate, *, generator='print(7)', reference='print(input())',
                 extra=()):
        with tempfile.TemporaryDirectory(prefix='stress test ') as directory:
            root = Path(directory)
            for name, code in [('gen', generator), ('ref', reference), ('sol', candidate)]:
                (root / (name + '.py')).write_text(code, encoding='utf-8')
            command = [sys.executable, str(SCRIPT)]
            for name in ['gen', 'ref', 'sol']:
                command += ['--' + name, sys.executable, str(root / (name + '.py'))]
            result = subprocess.run([*command, '--tests', '2', '--timeout', '3', *extra],
                                    cwd=root, capture_output=True, text=True, timeout=20)
            saved = {p.name: p.read_bytes() for p in root.glob('*.txt')}
            saved.update({p.name: p.read_bytes() for p in root.glob('*.err')})
            return result, saved

    def test_token_comparison_and_strict_mode(self):
        code = "print('  ' + input() + '  ')"
        result, _ = self.run_case(code)
        self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        self.assertIn('PASS: 2 tests', result.stdout)
        result, saved = self.run_case(code, extra=['--strict'])
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('Test 1: WA', result.stdout)
        self.assertEqual(saved['data.txt'].split(), [b'7'])
        self.assertEqual(saved['biaoda.txt'].split(), saved['aatest.txt'].split())

    def test_wrong_answer_preserves_counterexample(self):
        result, saved = self.run_case('print(int(input()) + 1)')
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('Test 1: WA', result.stdout)
        self.assertNotIn('Test 2', result.stdout)
        self.assertEqual(saved['biaoda.txt'].strip(), b'7')
        self.assertEqual(saved['aatest.txt'].strip(), b'8')

    def test_failure_in_each_process_is_reported(self):
        failure = "import sys; print('broken', file=sys.stderr); sys.exit(7)"
        for name, role in [('generator', 'gen'), ('reference', 'ref'), ('candidate', 'sol')]:
            with self.subTest(role=role):
                kwargs = {'candidate': 'print(input())', name: failure}
                result, saved = self.run_case(**kwargs)
                self.assertNotEqual(result.returncode, 0)
                self.assertIn(('solution' if role == 'sol' else name) + ' RE (exit 7)',
                              result.stdout)
                self.assertIn(b'broken', saved[role + '.err'])

    def test_timeout_and_missing_executable(self):
        result, saved = self.run_case('import time; time.sleep(5)',
                                      extra=['--timeout', '0.5'])
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('solution TLE', result.stdout)
        self.assertEqual(saved['data.txt'].strip(), b'7')
        result, _ = self.run_case('print(input())', extra=['--sol', 'no-such-solver-123456'])
        self.assertNotEqual(result.returncode, 0)
        self.assertIn('solution ERROR', result.stdout)


if __name__ == '__main__':
    unittest.main()
