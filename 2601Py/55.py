# 072440632 李欣晨
import numpy as np

arr = np.random.randint(0, 10, 10)
print("原始数组:", arr)

arr[arr.argmax()] = 100

print("修改后的数组:", arr)
