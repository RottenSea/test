# 072440632李欣晨
import matplotlib.pyplot as plt

plt.rcParams["font.sans-serif"] = ["SimHei", "Microsoft YaHei"]
plt.rcParams["axes.unicode_minus"] = False

labels = ["上课", "自习", "娱乐", "睡眠", "用餐", "其他"]
sizes = [5, 3, 2, 8, 2, 4]
colors = ["#3498db", "#2ecc71", "#e74c3c", "#9b59b6", "#f39c12", "#95a5a6"]
explode = [0, 0, 0, 0.1, 0, 0]

plt.pie(
    sizes,
    labels=labels,
    colors=colors,
    explode=explode,
    autopct="%1.1f%%",
    startangle=90,
)
plt.title("大学生每日时间分配")
plt.show()
