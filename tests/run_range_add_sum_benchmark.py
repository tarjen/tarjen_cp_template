"""Compare the repository's range-add/range-sum BIT and segment tree."""
import argparse
import pathlib
import shutil
import subprocess
import tempfile


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--operations", type=int, default=500_000)
    parser.add_argument("--repeats", type=int, default=5)
    parser.add_argument("--sizes", type=int, nargs="+", default=[10_000, 100_000, 1_000_000])
    parser.add_argument("--compiler", default="g++")
    args = parser.parse_args()
    if min(args.operations, args.repeats, *args.sizes) < 1:
        parser.error("operations, repeats and sizes must be positive")
    compiler = shutil.which(args.compiler)
    if not compiler:
        parser.error(f"compiler not found: {args.compiler}")
    source = pathlib.Path(__file__).with_name("range_add_sum_benchmark.cpp")
    with tempfile.TemporaryDirectory(prefix="range-add-sum-benchmark-") as tmp:
        binary = pathlib.Path(tmp) / "benchmark.exe"
        subprocess.run(
            [compiler, "-std=c++17", "-O2", "-DNDEBUG", "-Wall", "-Wextra", "-Werror",
             str(source), "-o", str(binary)], check=True,
        )
        subprocess.run(
            [str(binary), str(args.operations), str(args.repeats), *map(str, args.sizes)],
            check=True,
        )


if __name__ == "__main__":
    main()
