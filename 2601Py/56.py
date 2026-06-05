# 072440632 李欣晨
import numpy as np

arr = np.arange(20)
print("数组:", arr)

a = np.random.uniform(0, 20)
print(f"给定值 a: {a:.2f}")

index = (np.abs(arr - a)).argmin()

print(f"数组中最接近 {a:.2f} 的值是: {arr[index]}")
