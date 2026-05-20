# import numpy as np

# a = np.float64(23)
# print("证书转化为浮点数:", a)

# b = np.int8(9.0)
# print("浮点数转化为整数:", b)

# c = np.bool(2)
# print("整数转化为布尔类型数据:", c)

# d = np.bool(2.0)
# print("浮点数转化为布尔类型数据:", d)


# import numpy as np

# a = np.array([1, 2, 3, 4, 5])
# print(a)

# x = np.zeros((3, 4))
# print("x=", x)

# y = np.ones((2, 3, 4), dtype=int)
# print("y=", y)

# z = np.empty((3, 2), dtype=int)
# print("z=", z)


# import numpy as np

# a = np.atange(9).reshape(3, 3)
# print("a=", a)

# b = 2 * a
# print("b=", b)

# print("水平组合1:", np.hstack((a, b)))
# print("水平组合2:", np.concatenate((a, b), axis=1))

# print("垂直组合1:", np.vstack((a, b)))

# print("垂直组合2:", np.concatenate((a, b), axis=0))

# print("深度组合:", np.dstack((a, b)))

# 072440632李欣晨
import numpy as np

arr = np.arange(15).reshape(3, 5)

print("数组内容:\n", arr)
print("数组维度:", arr.shape)
print("总元素个数:", arr.size)
print("数据类型:", arr.dtype)
