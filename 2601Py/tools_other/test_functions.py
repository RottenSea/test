import numpy as np

def sphere(x):
    """Sphere 函数：单峰，理论最优 0，最优位置 [0,...,0]"""
    return np.sum(x ** 2)

def rastrigin(x):
    """Rastrigin 函数：多峰，理论最优 0，最优位置 [0,...,0]"""
    return np.sum(x ** 2 - 10 * np.cos(2 * np.pi * x) + 10)

def griewank(x):
    """Griewank 函数：多峰，理论最优 0，最优位置 [0,...,0]
    通用维度版本，支持任意维度输入"""
    sum_part = np.sum(x ** 2) / 4000
    prod_part = np.prod([np.cos(x[i] / np.sqrt(i + 1)) for i in range(len(x))])
    return sum_part - prod_part + 1
