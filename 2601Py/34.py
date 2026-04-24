# 名字:李欣晨 072440632


def func2(lst, tup):
    res_lst = [lst[i] for i in range(1, len(lst), 2)]
    res_tup = [tup[i] for i in range(1, len(tup), 2)]
    return res_lst, res_tup


list_data = [1, 2, 3, 4, 5, 6, 7, 8, 9]
tuple_data = (1, 2, 3, 11, 21, 4, 5, 6, 7)

result = func2(list_data, tuple_data)
print(result)
