# 072440632李欣晨
import matplotlib.pyplot as plt
import numpy as np

plt.rcParams["font.sans-serif"] = ["SimHei", "Microsoft YaHei"]
plt.rcParams["axes.unicode_minus"] = False

x = np.arange(1, 8)
y1 = [40, 30, 50, 70, 40, 100, 90]
y2 = [50, 70, 30, 20, 70, 80, 70]

plt.bar(x - 0.15, y1, width=0.3, label="消费A", color="blue")
plt.bar(x + 0.15, y2, width=0.3, label="消费B", color="red")

plt.xticks(x, ["周一", "周二", "周三", "周四", "周五", "周六", "周日"])
plt.xlabel("星期")
plt.ylabel("消费金额")
plt.title("一周消费情况对比")
plt.legend()
plt.show()
