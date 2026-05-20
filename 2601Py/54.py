# 072440632李欣晨
import numpy as np

arr2 = np.zeros((6, 6), dtype=int)

arr2[0, :] = 6
arr2[-1, :] = 6
arr2[:, 0] = 6
arr2[:, -1] = 6

print("\n修改后的6*6数组:")
print(arr2)
