# 创建一个包含 1 到 10 的列表
my_list = [i for i in range(1, 11)]

print("创建的列表为:", my_list)

my_list.append(11)
print("添加元素后的列表:", my_list)

value_to_remove = 5
if value_to_remove in my_list:
    my_list.remove(value_to_remove)
print(f"删除元素 {value_to_remove} 后的列表:", my_list)

# 使用列表推导式生成一个偶数列表
even_list = [x for x in range(1, 21) if x % 2 == 0]
print("生成的偶数列表:", even_list)
