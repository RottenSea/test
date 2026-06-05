import matplotlib.pyplot as plt
import numpy as np


def fun(x, y):
    return np.power(x, 2) + np.power(y, 2)


fig = plt.figure()
ax = fig.add_subplot(111, projection="3d")
x = np.arange(-2, 2, 0.1)
y = np.arange(-2, 2, 0.1)
x, y = np.meshgrid(x, y)
z = fun(x, y)
ax.plot_surface(x, y, z)
plt.show()
