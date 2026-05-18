# 导入numpy数值计算库，用于数组创建、随机数、数学运算
import numpy as np

# 导入matplotlib绘图库，用于绘制收敛曲线
import matplotlib.pyplot as plt

# ===================== 绘图配置：彻底解决负号显示异常 =====================
# 重置matplotlib所有默认配置，避免字体冲突
plt.rcdefaults()
# 强制使用ASCII负号，解决负号显示为方框的问题
plt.rcParams["axes.unicode_minus"] = False
# 设置绘图画布默认大小
plt.rcParams["figure.figsize"] = (10, 5)


# ===================== 1. 定义2维优化测试函数 =====================
# Sphere函数：单峰函数，理论最优值=0，最优位置[0,0]
def fun1(x):
    # 计算输入向量的平方和，返回适应度值（越小越优）
    return np.sum(x**2)


# Rastrigin函数：多峰函数，理论最优值=0，最优位置[0,0]
def fun2(x):
    # 经典多峰测试函数公式，返回适应度值
    return np.sum(x**2 - 10 * np.cos(2 * np.pi * x) + 10)


# Griewank函数：复杂多峰函数，理论最优值=0，最优位置[0,0]
def fun3(x):
    # 计算平方和分项
    sum_part = np.sum(x**2) / 4000
    # 计算余弦乘积分项（2维专用）
    prod_part = np.cos(x[0] / np.sqrt(1)) * np.cos(x[1] / np.sqrt(2))
    # 组合得到函数最终值
    return sum_part - prod_part + 1


# ===================== 2. 象群优化算法(EHO) 核心实现 =====================
def EHO(obj_fun, dim, pop_size, max_iter, lb, ub):
    """
    象群优化算法
    :param obj_fun: 目标优化函数
    :param dim: 优化维度（这里固定为2）
    :param pop_size: 大象种群数量
    :param max_iter: 最大迭代次数
    :param lb: 搜索范围下界
    :param ub: 搜索范围上界
    :return: 最优位置、最优适应度、收敛曲线
    """
    # --------------------- EHO算法核心参数 ---------------------
    alpha = 0.5  # 母象族群更新系数（控制向族长靠拢的程度）
    beta = 0.1  # 公象分离系数（控制公象随机游走的程度）
    num_clan = 5  # 象群分为5个母象族群

    # --------------------- 初始化大象种群位置 ---------------------
    # 随机生成初始种群：pop_size只大象，dim维坐标，范围[lb,ub]
    population = np.random.uniform(lb, ub, (pop_size, dim))
    # 初始化适应度数组：存储每只大象的适应度值
    fitness = np.zeros(pop_size)

    # --------------------- 计算初始种群适应度 ---------------------
    for i in range(pop_size):
        # 计算第i只大象的适应度值
        fitness[i] = obj_fun(population[i])

    # --------------------- 初始化全局最优 ---------------------
    # 找到初始种群中适应度最小的索引
    best_idx = np.argmin(fitness)
    # 全局最优位置
    best_pos = population[best_idx].copy()
    # 全局最优适应度
    best_fit = fitness[best_idx]
    # 收敛曲线列表：记录每一代最优适应度
    convergence_curve = np.zeros(max_iter)

    # --------------------- 算法主迭代循环 ---------------------
    for t in range(max_iter):
        # 计算每个族群的大象数量
        clan_size = pop_size // num_clan
        # 遍历每一个母象族群，更新族群内大象位置
        for c in range(num_clan):
            # 当前族群的起始索引
            start = c * clan_size
            # 当前族群的结束索引
            end = start + clan_size
            # 提取当前族群的所有大象
            clan_ele = population[start:end]
            # 提取当前族群所有大象的适应度
            clan_fit = fitness[start:end]

            # 找到当前族群的最优大象（族长）
            clan_best_idx = np.argmin(clan_fit)
            # 族长位置
            clan_best_pos = clan_ele[clan_best_idx]

            # 更新当前族群内的每一只母象（核心行为1：跟随族长）
            for i in range(clan_size):
                # 生成0~1的随机数
                r1 = np.random.rand()
                # 母象位置更新公式：向族长靠拢
                new_pos = alpha * clan_best_pos + r1 * (ub - lb) * clan_ele[i]
                # 边界约束：限制在搜索范围内
                new_pos = np.clip(new_pos, lb, ub)
                # 计算新位置的适应度
                new_fit = obj_fun(new_pos)

                # 贪心更新：如果新位置更优，就替换
                if new_fit < clan_fit[i]:
                    population[start + i] = new_pos
                    fitness[start + i] = new_fit

        # --------------------- 更新公象（核心行为2：独立分离） ---------------------
        for i in range(pop_size):
            # 生成0~1的随机数
            r2 = np.random.rand()
            # 公象位置更新公式：随机游走，远离族群
            new_pos = beta * r2 * best_pos - population[i]
            # 边界约束
            new_pos = np.clip(new_pos, lb, ub)
            # 计算新适应度
            new_fit = obj_fun(new_pos)

            # 贪心更新
            if new_fit < fitness[i]:
                population[i] = new_pos
                fitness[i] = new_fit

        # --------------------- 更新全局最优解 ---------------------
        # 找到当前种群最优索引
        current_best_idx = np.argmin(fitness)
        # 当前种群最优适应度
        current_best_fit = fitness[current_best_idx]

        # 如果当前最优比全局最优更优，更新全局最优
        if current_best_fit < best_fit:
            best_fit = current_best_fit
            best_pos = population[current_best_idx].copy()

        # 记录当前迭代的最优值到收敛曲线
        convergence_curve[t] = best_fit

    # 返回最终结果：最优位置、最优适应度、收敛曲线
    return best_pos, best_fit, convergence_curve


# ===================== 3. 主程序：运行算法 + 输出结果 + 绘图 =====================
if __name__ == "__main__":
    # --------------------- 算法参数设置 ---------------------
    dim = 2  # 优化维度：固定2维
    pop_size = 30  # 大象种群数量：30只
    max_iter = 300  # 最大迭代次数：300次
    lb = -10  # 搜索范围下界
    ub = 10  # 搜索范围上界

    # --------------------- 运行EHO算法优化3个测试函数 ---------------------
    # 优化Sphere函数
    pos1, val1, curve1 = EHO(fun1, dim, pop_size, max_iter, lb, ub)
    # 优化Rastrigin函数
    pos2, val2, curve2 = EHO(fun2, dim, pop_size, max_iter, lb, ub)
    # 优化Griewank函数
    pos3, val3, curve3 = EHO(fun3, dim, pop_size, max_iter, lb, ub)

    # --------------------- 打印优化结果 ---------------------
    print("=" * 60)
    print("Elephant Herding Optimization (EHO) 2D Results")
    print("=" * 60)
    # 输出Sphere函数结果（保留4位小数）
    print(f"Sphere: Best Position = {np.round(pos1, 4)} | Best Value = {val1:.8f}")
    # 输出Rastrigin函数结果
    print(f"Rastrigin: Best Position = {np.round(pos2, 4)} | Best Value = {val2:.8f}")
    # 输出Griewank函数结果
    print(f"Griewank: Best Position = {np.round(pos3, 4)} | Best Value = {val3:.8f}")
    print("=" * 60)

    # --------------------- 绘制收敛曲线 ---------------------
    # 绘制Sphere函数收敛曲线（红色）
    plt.semilogy(curve1, label="Sphere", color="red", linewidth=2)
    # 绘制Rastrigin函数收敛曲线（蓝色）
    plt.semilogy(curve2, label="Rastrigin", color="blue", linewidth=2)
    # 绘制Griewank函数收敛曲线（绿色）
    plt.semilogy(curve3, label="Griewank", color="green", linewidth=2)
    # X轴标签：迭代次数
    plt.xlabel("Iteration")
    # Y轴标签：适应度值（对数尺度）
    plt.ylabel("Fitness (Log Scale)")
    # 图表标题
    plt.title("2D EHO Algorithm Convergence Curve")
    # 显示图例
    plt.legend()
    # 显示网格线
    plt.grid(True, alpha=0.3)
    # 显示图像
    plt.show()
