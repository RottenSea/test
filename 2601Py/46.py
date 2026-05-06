f = open(
    r"C:\Users\RottenTh\Desktop\Archived\Repository\test\2601Py\text.txt",
    "r",
    encoding="utf-8",
)


print(f.tell())
f.seek(10, 0)
