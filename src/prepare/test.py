import os
import sys
import zipfile

c = sys.argv[1]
code = c.capitalize()
os.system(f'g++ {c}.cpp -O2 -Wall -o {c}.exe')
try:
    x = zipfile.Zipfile(f'samples-{code}.zip')
    x.extractall(f'samples-{code}')
except:
    pass

for i in range(1,10000):
    if not os.path.isfile(f'samples-{code}/{i}.ans'):
        break
    print(f'Test {i}')
    os.system(f'{c}.exe < samples-{code}/{i}.in > samples-{code}/{i}.out')
    out = open(f'samples-{code}/{i}.out').read().replace('\r\n','\n')
    ans = open(f'samples-{code}/{i}.ans').read().replace('\r\n','\n')
    if(out != ans):
        print(f'WA {i}')
    else:
        print(f'AC {i}')