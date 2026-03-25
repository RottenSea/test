a = int(input("请输入数字 a (1-9): "))
n = int(input("请输入项数 n: "))

s = 0
current_term = 0

for i in range(n):
    current_term = current_term * 10 + a
    s += current_term

print(f"s = {s}")
