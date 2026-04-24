# 名字:李欣晨 072440632


def func5(s):
    length = len(s)
    for i in range(length // 2):
        if s[i] != s[length - 1 - i]:
            return i + 1
    return True


print(func5("abcddcbaa"))
print(func5("pythono0htyp"))
print(func5("bookkoob"))
