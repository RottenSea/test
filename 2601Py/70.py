import matplotlib.pyplot as plt
import csv
import os

plt.rcParams["font.sans-serif"] = ["SimHei"]
plt.rcParams["axes.unicode_minus"] = False

base = os.path.dirname(os.path.abspath(__file__))
quarters = []
counts = []
with open(os.path.join(base, "tools_other", "data.csv"), encoding="utf-8") as f:
    reader = csv.DictReader(f)
    for row in reader:
        quarters.append(row["季度"])
        counts.append(int(row["人数"]))

plt.bar(quarters, counts, color="skyblue")
plt.xlabel("季度")
plt.ylabel("出生人数")
plt.title("班级不同季度出生人数分布")
plt.show()
