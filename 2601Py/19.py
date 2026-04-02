import random

# 定义并生成随机列表：使用列表推导式生成10个1到10之间的随机整数
original_list = [random.randint(1, 10) for _ in range(10)]

# 初始化目标字典：提前定义好键 k1 和 k2
result = {"k1": [], "k2": []}

# 遍历列表并按条件分类：
# 小于 6 的放入 k1，其他的（即大于等于 6）放入 k2
for value in original_list:
    if value < 6:
        result["k1"].append(value)
    else:
        result["k2"].append(value)

# 对分类后的列表进行从小到大排序
# 使用 .sort() 方法在原位进行排序
result["k1"].sort()
result["k2"].sort()

# 输出结果
print("生成的原始列表:", original_list)
print("分类并排序后的字典:", result)
