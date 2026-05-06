# 李欣晨 0f72440632

with open("2601Py/A.txt", "r", encoding="utf-8") as f:
    names = f.readlines()

pure_numbers = []
for name in names:
    name = name.strip()
    if name.isdigit():
        pure_numbers.append(name)

with open("B.txt", "w", encoding="utf-8") as f:
    for name in pure_numbers:
        f.write(name + "\n")

print("完成！纯数字的名字已保存到 B.txt")
