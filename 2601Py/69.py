# 李欣晨 072440632

import matplotlib.pyplot as plt

plt.rcParams["font.sans-serif"] = ["SimHei"]
plt.rcParams["axes.unicode_minus"] = False

labels = ["中专", "大专", "本科", "硕士", "其他"]
sizes = [0.2515, 0.3724, 0.3336, 0.0368, 0.0057]
colors = ["#3498db", "#2ecc71", "#e74c3c", "#9b59b6", "#95a5a6"]
explode = [0, 0.05, 0, 0, 0]

plt.pie(
    sizes,
    labels=labels,
    colors=colors,
    explode=explode,
    autopct="%1.2f%%",
    startangle=90,
)
plt.title("失信人员教育水平分布")
plt.show()
