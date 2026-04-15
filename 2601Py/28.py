s = input("请输入字符串: ")
sorted_s = "".join(sorted(s))
res = sorted_s[::-1] + sorted_s
print(res)
