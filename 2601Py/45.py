f = open(
    r"C:\Users\RottenTh\Desktop\Archived\Repository\test\2601Py\text.txt",
    "r",
    encoding="utf-8",
)
last_name = f.readlines()
f.close()
last_name = [x[:-1] for x in last_name]
print(last_name)

dic = {}

for name in last_name:
    n = name[0]
    dic[n] = dic.get(n, 0) + 1
print(dic)
