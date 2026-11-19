import os
import sys
# linux下去掉.exe 和 加./
c = sys.argv[1]
d = f'samples-{c.capitalize()}'
os.system(f'g++ {c}.cpp -O2 -Wall -o {c}.exe')

for i in range(1,10000):
    p = f'{d}/{i}'
    if not os.path.isfile(f'{p}.ans'):
        break
    print(f'Test {i}')
    os.system(f'{c}.exe < {p}.in > {p}.out')
    out = open(f'{p}.out').read().replace('\r\n','\n')
    ans = open(f'{p}.ans').read().replace('\r\n','\n')
    if(out != ans):
        print(f'WA {i}')
    else:
        print(f'AC {i}')
