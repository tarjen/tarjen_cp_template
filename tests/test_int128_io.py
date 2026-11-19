"""Check signed decimal I/O against Python integers for both source variants."""
from pathlib import Path
import os
import random
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[1]


class Int128IOTests(unittest.TestCase):
    def test_signed_boundaries_and_random_values(self):
        values = [0, 1, -1, 12, -12, (1 << 127) - 1, -(1 << 127),
                  -(1 << 127) + 1, 1 << 100, -(1 << 100),
                  (1 << 63) - 1, -(1 << 63)]
        rng = random.Random(20261115)
        values += [rng.randrange(-(1 << 127), 1 << 127) for _ in range(300)]
        tokens = [str(x) for x in values] + ['+12', '+0', '-0', '00012', '-00012']
        expected = ''.join(f'{int(x)}\n' for x in tokens)
        # 最后一个整数后不加换行，覆盖数字后直接 EOF 的情况。
        data = str(len(tokens)) + '\n' + '\t \n'.join(tokens)
        with tempfile.TemporaryDirectory(prefix='int128-io-') as directory:
            executable = Path(directory) / ('check.exe' if os.name == 'nt' else 'check')
            for variant in ('full', 'handcopy'):
                flags = ['-DACM_VARIANT'] if variant == 'handcopy' else []
                subprocess.run(['g++', '-std=c++17', '-O1', '-Wall', '-Wextra',
                                *flags, str(ROOT / 'tests/int128_io.cpp'),
                                '-o', str(executable)], check=True)
                with self.subTest(variant=variant):
                    result = subprocess.run([str(executable)], input=data,
                                            capture_output=True, text=True,
                                            timeout=10, check=True)
                    self.assertEqual(result.stdout, expected)


if __name__ == '__main__':
    unittest.main()
