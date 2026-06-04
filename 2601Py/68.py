import matplotlib.pyplot as plt
import numpy as np
import xlrd

plt.rcParams["font.sans-serif"] = ["SimHei"]
plt.rcParams["axes.unicode_minus"] = False
xls = xlrd.open_workbook(r"123.xlsm")
table = xls.sheets()[1]
x = []
y = []
for i in range(table.nrows):
    if i == 0:
        x = table.row_values(i)
    else:
        y = table.row_values(i)

plt.xlabel("x: food neme")
plt.ylabel("y: woter percentage")
plt.title("food water percentage")
plt.bar(x, y)
plt.show()
