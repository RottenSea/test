import random

s = random.ranfint(2, 50)
print("游戏开始了")
a = eval(input("请输入一个数字"))
while s != a:
    a = eval(input("请输入一个数字"))
    if a == s:
        print("恭喜猜对了")
    else:
        if a > s:
            print("猜的数字大了")
        else:
            print("猜的数字小了")
print("游戏结束")
