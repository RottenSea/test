# 导入数值计算库numpy，用于数组操作、随机数生成和数学计算
import numpy as np

# 导入matplotlib绘图库，用于绘制算法收敛曲线图
import matplotlib.pyplot as plt
import math

# 重置matplotlib的所有默认配置，清除历史设置冲突
plt.rcdefaults()
# 核心修复：强制matplotlib使用ASCII负号，解决负号显示为方框的问题
plt.rcParams["axes.unicode_minus"] = False
# 设置绘图画布的默认尺寸为宽10、高5
plt.rcParams["figure.figsize"] = (10, 5)


# ===================== 1. 定义2维测试目标函数 =====================
# Sphere函数：2维单峰测试函数，理论最优值=0，最优位置[0,0]
def fun1(x):
    # 计算输入向量所有元素的平方和，返回函数适应度值
    return np.sum(x**2)


# Rastrigin函数：2维多峰测试函数，理论最优值=0，最优位置[0,0]
def fun2(x):
    # 经典多峰函数计算公式，返回函数适应度值
    return np.sum(x**2 - 10 * np.cos(2 * np.pi * x) + 10)


# Griewank函数：2维复杂多峰测试函数，理论最优值=0，最优位置[0,0]
def fun3(x):
    # 计算函数的平方和分项
    sum_part = np.sum(x**2) / 4000
    # 计算函数的余弦乘积分项（2维专用）
    prod_part = np.cos(x[0] / np.sqrt(1)) * np.cos(x[1] / np.sqrt(2))
    # 组合两项得到最终函数值并返回
    return sum_part - prod_part + 1


# ===================== 2. 莱维飞行函数 =====================
# 生成莱维飞行步长，用于增强算法全局搜索能力
def levy_flight(dim, beta=1.5):
    # 计算莱维飞行公式中的标准差sigma（标准数学公式）
    sigma = (
        math.gamma(1 + beta)
        * np.sin(np.pi * beta / 2)
        / (math.gamma((1 + beta) / 2) * beta * 2 ** ((beta - 1) / 2))
    ) ** (1 / beta)
    # 生成均值为0、标准差为sigma的正态分布随机数u
    u = np.random.normal(0, sigma, dim)
    # 生成标准正态分布随机数v
    v = np.random.normal(0, 1, dim)
    # 计算最终的莱维飞行步长并返回
    step = u / (np.abs(v) ** (1 / beta))
    return step


# ===================== 3. 2维蜻蜓优化算法主函数 =====================
# 输入：目标函数、维度、种群数、最大迭代次数、搜索上下界
def DragonflyAlgorithm(obj_fun, dim, pop_num, max_iter, lb, ub):
    # 随机初始化蜻蜓种群位置：pop_num只蜻蜓，dim维坐标，范围[lb,ub]
    dragon_pos = np.random.uniform(lb, ub, (pop_num, dim))
    # 初始化蜻蜓的飞行步长（速度），初始值全为0
    dragon_step = np.zeros((pop_num, dim))
    # 创建空列表，存储每一代的全局最优值，用于绘制收敛曲线
    iter_curve = []

    # 蜻蜓算法五大核心行为权重（官方标准参数）
    w = 0.7  # 惯性权重：保留上一代的飞行方向
    s = 0.2  # 分离权重：避免蜻蜓之间相互碰撞
    a = 0.3  # 对齐权重：与种群保持相同的飞行速度
    c = 0.4  # 聚集权重：向种群中心位置靠拢
    f = 0.5  # 食物吸引权重：向全局最优解方向飞行
    e = 0.1  # 天敌排斥权重：远离全局最差解方向

    # 初始化食物位置（全局最优解），维度与问题一致
    food_pos = np.zeros(dim)
    # 初始化食物适应度（最优值），设为无穷大（求最小值）
    food_fit = float("inf")
    # 初始化天敌位置（全局最差解），维度与问题一致
    enemy_pos = np.zeros(dim)
    # 初始化天敌适应度（最差值），设为负无穷大
    enemy_fit = -float("inf")

    # 遍历初始种群，寻找第一代的最优和最差个体
    for i in range(pop_num):
        # 计算当前第i只蜻蜓的适应度值
        fit = obj_fun(dragon_pos[i])
        # 如果当前适应度更小，更新全局最优解（食物）
        if fit < food_fit:
            food_fit, food_pos = fit, dragon_pos[i].copy()
        # 如果当前适应度更大，更新全局最差解（天敌）
        if fit > enemy_fit:
            enemy_fit, enemy_pos = fit, dragon_pos[i].copy()

    # 算法主迭代循环，执行max_iter次寻优
    for it in range(max_iter):
        # 动态更新惯性权重：随迭代线性衰减，前期全局搜索，后期局部搜索
        w = 0.9 - it * 0.5 / max_iter

        # 遍历种群中的每一只蜻蜓，更新位置和步长
        for i in range(pop_num):
            # 初始化分离行为向量
            separate = np.zeros(dim)
            # 初始化对齐行为向量
            align = np.zeros(dim)
            # 初始化聚集行为向量
            gather = np.zeros(dim)
            # 统计相邻蜻蜓数量，用于行为归一化
            count = 0

            # 遍历所有其他蜻蜓，计算群体交互行为
            for j in range(pop_num):
                # 排除自身，只计算与其他蜻蜓的交互
                if i != j:
                    # 累加分离行为：远离其他蜻蜓
                    separate += dragon_pos[i] - dragon_pos[j]
                    # 累加对齐行为：同步其他蜻蜓的飞行步长
                    align += dragon_step[j]
                    # 累加聚集行为：向其他蜻蜓位置靠拢
                    gather += dragon_pos[j]
                    # 相邻蜻蜓数量+1
                    count += 1

            # 如果存在相邻蜻蜓，对行为向量归一化，保证数值稳定
            if count > 0:
                separate = -separate / count
                align = align / count
                gather = (gather / count) - dragon_pos[i]

            # 计算食物吸引：向全局最优解方向移动
            food_att = food_pos - dragon_pos[i]
            # 计算天敌排斥：远离全局最差解方向移动
            enemy_rep = enemy_pos + dragon_pos[i]

            # 综合所有行为，计算蜻蜓的新飞行步长
            step = (
                w * dragon_step[i]
                + s * separate
                + a * align
                + c * gather
                + f * food_att
                - e * enemy_rep
            )
            # 限制步长范围在[-2,2]，防止步长过大导致算法震荡
            dragon_step[i] = np.clip(step, -2, 2)

            # 20%的概率执行莱维飞行，增强全局搜索，跳出局部最优
            if np.random.rand() < 0.2:
                # 莱维飞行更新位置，步长缩放0.1保证稳定性
                new_pos = dragon_pos[i] + levy_flight(dim) * 0.1
            # 80%的概率按照常规行为更新位置
            else:
                # 常规位置更新：当前位置 + 飞行步长
                new_pos = dragon_pos[i] + dragon_step[i]

            # 边界约束：强制蜻蜓位置在搜索范围[lb,ub]内，防止越界
            dragon_pos[i] = np.clip(new_pos, lb, ub)

            # 计算更新位置后当前蜻蜓的适应度值
            curr_fit = obj_fun(dragon_pos[i])
            # 更新全局最优解（食物）
            if curr_fit < food_fit:
                food_fit, food_pos = curr_fit, dragon_pos[i].copy()
            # 更新全局最差解（天敌）
            if curr_fit > enemy_fit:
                enemy_fit, enemy_pos = curr_fit, dragon_pos[i].copy()

        # 将当前迭代的最优适应度值存入收敛曲线列表
        iter_curve.append(food_fit)

    # 迭代结束，返回：最优位置坐标、最优函数值、收敛曲线数据
    return food_pos, food_fit, iter_curve


# ===================== 4. 主程序运行入口 =====================
if __name__ == "__main__":
    # 设置优化问题维度：2维（固定）
    dim = 2
    # 设置蜻蜓种群数量：30只
    pop = 30
    # 设置算法最大迭代次数：300次
    max_iter = 300
    # 设置搜索范围下界：-10
    lb = -10
    # 设置搜索范围上界：10
    ub = 10

    # 运行蜻蜓算法，优化Sphere函数
    pos1, val1, curve1 = DragonflyAlgorithm(fun1, dim, pop, max_iter, lb, ub)
    # 运行蜻蜓算法，优化Rastrigin函数
    pos2, val2, curve2 = DragonflyAlgorithm(fun2, dim, pop, max_iter, lb, ub)
    # 运行蜻蜓算法，优化Griewank函数
    pos3, val3, curve3 = DragonflyAlgorithm(fun3, dim, pop, max_iter, lb, ub)

    # 打印分割线，美化输出格式
    print("=" * 60)
    # 打印算法结果标题
    print("2D Dragonfly Algorithm Results")
    # 打印分割线
    print("=" * 60)
    # 打印Sphere函数的最优坐标和最优值（保留4位小数）
    print(f"Sphere: Best Position = {np.round(pos1,4)} | Best Value = {val1:.8f}")
    # 打印Rastrigin函数的最优坐标和最优值（保留4位小数）
    print(f"Rastrigin: Best Position = {np.round(pos2,4)} | Best Value = {val2:.8f}")
    # 打印Griewank函数的最优坐标和最优值（保留4位小数）
    print(f"Griewank: Best Position = {np.round(pos3,4)} | Best Value = {val3:.8f}")
    # 打印分割线
    print("=" * 60)

    # 绘制Sphere函数收敛曲线（红色）
    plt.semilogy(curve1, label="Sphere", color="red")
    # 绘制Rastrigin函数收敛曲线（蓝色）
    plt.semilogy(curve2, label="Rastrigin", color="blue")
    # 绘制Griewank函数收敛曲线（绿色）
    plt.semilogy(curve3, label="Griewank", color="green")
    # 设置X轴标签：迭代次数
    plt.xlabel("Iteration")
    # 设置Y轴标签：适应度值（对数尺度）
    plt.ylabel("Fitness (Log Scale)")
    # 设置图表标题
    plt.title("2D Dragonfly Algorithm Convergence Curve")
    # 显示图例
    plt.legend()
    # 显示网格线，提升图表可读性
    plt.grid(True)
    # 显示绘制好的收敛曲线图
    plt.show()
