"""对拍：python duipai.py；先编译好 testin、abiaocheng、nedtest。
自定义：python duipai.py --gen python gen.py --ref ./std --sol ./main --tests 1000
默认按空白分隔的 token 比较；--strict 严格比较字节；--timeout 为单次秒数。
失败时保留 data.txt、biaoda.txt、aatest.txt 和各程序 stderr；不自动编译。
"""
import argparse
import os
from pathlib import Path
import subprocess
import sys


def run(command, source, target, errors, timeout):
    command = list(command)
    if Path(command[0]).is_file():
        command[0] = str(Path(command[0]).resolve())
    try:
        with (open(source, 'rb') if source else open(os.devnull, 'rb')) as inp:
            with open(target, 'wb') as out, open(errors, 'wb') as err:
                result = subprocess.run(command, stdin=inp, stdout=out, stderr=err,
                                        timeout=timeout)
        return None if result.returncode == 0 else f'RE (exit {result.returncode})'
    except subprocess.TimeoutExpired:
        return f'TLE ({timeout}s)'
    except OSError as error:
        return f'ERROR ({error})'


def main():
    suffix = '.exe' if os.name == 'nt' else ''
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--gen', nargs='+', default=['testin' + suffix])
    parser.add_argument('--ref', nargs='+', default=['abiaocheng' + suffix])
    parser.add_argument('--sol', nargs='+', default=['nedtest' + suffix])
    parser.add_argument('--tests', type=int, default=100000)
    parser.add_argument('--timeout', type=float, default=2.0)
    parser.add_argument('--strict', action='store_true')
    args = parser.parse_args()
    if args.tests <= 0 or not 0 < args.timeout < float('inf'):
        parser.error('--tests and --timeout must be positive and finite')
    for case in range(1, args.tests + 1):
        # 清空上一轮输出，生成器或标程失败时也不会误留旧答案。
        for name in ['biaoda.txt', 'aatest.txt', 'gen.err', 'ref.err', 'sol.err']:
            Path(name).write_bytes(b'')
        for role, command, source, target, errors in [
            ('generator', args.gen, None, 'data.txt', 'gen.err'),
            ('reference', args.ref, 'data.txt', 'biaoda.txt', 'ref.err'),
            ('solution', args.sol, 'data.txt', 'aatest.txt', 'sol.err'),
        ]:
            failure = run(command, source, target, errors, args.timeout)
            if failure:
                print(f'Test {case}: {role} {failure}; see {errors}', flush=True)
                return 1
        expected = Path('biaoda.txt').read_bytes()
        actual = Path('aatest.txt').read_bytes()
        equal = expected == actual if args.strict else expected.split() == actual.split()
        if not equal:
            print(f'Test {case}: WA; saved data.txt, biaoda.txt, aatest.txt', flush=True)
            return 1
        print(f'Test {case}: AC', flush=True)
    print(f'PASS: {args.tests} tests', flush=True)
    return 0


if __name__ == '__main__':
    sys.exit(main())
