import matplotlib.pyplot as plt
import numpy as np

plt.rcParams['font.sans-serif'] = ['SimHei', 'Microsoft YaHei']
plt.rcParams['axes.unicode_minus'] = False

x = np.arange(1, 8)
y1 = [40, 30, 50, 70, 40, 100, 90]
y2 = [50, 70, 30, 20, 70, 80, 70]
plt.bar(x, y1, width=0.3, facecolor="blue")
plt.bar(x + 0.3, y2, width=0.3, facecolor="red")
plt.legend()
plt.show()
