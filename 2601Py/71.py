# 李欣晨 072440632

import matplotlib.pyplot as plt
import numpy as np

plt.rcParams["font.sans-serif"] = ["SimHei"]
plt.rcParams["axes.unicode_minus"] = False

x = np.linspace(0, 2 * np.pi, 100)

ax1 = plt.subplot(2, 1, 1)
ax1.plot(x, np.sin(x), label="正弦")
ax1.plot(x, np.cos(x), label="余弦")
ax1.legend()
ax1.set_title("正弦和余弦")

ax2 = plt.subplot(2, 2, 3)
ax2.plot(x, np.sin(x), color="C0")
ax2.set_title("正弦")

ax3 = plt.subplot(2, 2, 4)
ax3.plot(x, np.cos(x), color="C1")
ax3.set_title("余弦")

plt.tight_layout()
plt.show()
