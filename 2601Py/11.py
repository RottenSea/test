sum = 0
for i in range(1, 51):
    if (i % 3 == 0) & (i % 5 != 0):
        print(f"{i}", end=" ")
        sum += i
print(f"和为：{sum}", end="")
