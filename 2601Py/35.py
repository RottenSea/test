# 名字:李欣晨 072440632


def func3(*args):
    if not args:
        return 0, []

    avg = sum(args) / len(args)
    greater_than_avg = [x for x in args if x > avg]

    return avg, greater_than_avg


result = func3(1, 3, 5, 7, 9, 2, 4, 6)
print(result)
