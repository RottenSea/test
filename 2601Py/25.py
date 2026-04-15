a = "hello"
b = "world"
print("{}and{}".format(a, b))
print("{:10s}and{:10s}".format(a, b))
print("{:^10s}and{:^10s}".format(a, b))

a = 24
b = a + 4
print(a, "级计算机学生", b, "年毕业")
print("%10d级计算机学生%-5d年毕业" % (a, b))
print("%10d级计算机学生%-5d年毕业" % (a, b))
