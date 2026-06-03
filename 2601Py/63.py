import matplotlib.pyplot as plt
import numpy as np

plt.rcParams['font.sans-serif'] = ['SimHei', 'Microsoft YaHei']
plt.rcParams['axes.unicode_minus'] = False

data = [15, 45, 30, 10]
labels = ["a", "b", "c", "d"]
explodes = (0, 0.1, 0, 0)

plt.pie(data, labels=labels, radius=1, explode=explodes, autopct="%1.1f%%")
plt.show()
