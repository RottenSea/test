# 名字:李欣晨 072440632


def func4(lst):
    if not lst:
        return None

    max_val = lst[0]
    for num in lst:
        if num > max_val:
            max_val = num
    return max_val


lst = [14, 2, 21, 6, 7, 9, 11]
result = func4(lst)
print(result)
