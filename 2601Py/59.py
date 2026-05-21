import os, re

dir_path = os.path.join(os.path.dirname(__file__), '..', '平凡的真理_split')
total = 0
for f in sorted(os.listdir(dir_path)):
    if f.endswith('.txt'):
        text = open(os.path.join(dir_path, f), 'r', encoding='utf-8').read()
        count = len(re.sub(r'\s', '', text))
        total += count
        print(f'{f}: {count}')

print(f'\n总字数: {total}')
