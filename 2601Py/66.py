# 072440632李欣晨
import matplotlib.pyplot as plt
import numpy as np

plt.rcParams["font.sans-serif"] = ["SimHei", "Microsoft YaHei"]
plt.rcParams["axes.unicode_minus"] = False

x = [1, 2, 3, 4, 5, 6, 7]
y_bar = [45, 60, 55, 50, 70, 65, 58]
y_line = [6, 7, 5, 8, 6, 5, 7]

fig, ax1 = plt.subplots()

ax1.bar(x, y_bar, width=0.5, color="blue", alpha=0.7, label="日均消费")
ax1.set_xlabel("星期")
ax1.set_ylabel("消费金额", color="blue")
ax1.set_xticks(x)
ax1.set_xticklabels(["周一", "周二", "周三", "周四", "周五", "周六", "周日"])

ax2 = ax1.twinx()
ax2.plot(
    x, y_line, color="red", marker="o", linestyle="-", linewidth=2, label="日均学习时长"
)
ax2.set_ylabel("学习时长（小时）", color="red")

fig.suptitle("一周学习与消费情况对比")
fig.legend(loc="upper right")
plt.show()
