# 李欣晨 072440632

with open("2601Py/N.txt", "r", encoding="utf-8") as f:
    content = f.read()

numbers = []
for ch in content:
    if ch.isdigit():
        numbers.append(int(ch))

numbers.sort()
print(numbers)
