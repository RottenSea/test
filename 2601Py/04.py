import random

secret = random.randint(1, 10)
print("_______Guess the Number_______")
guess = 0
while guess != secret:
    temp = input("不妨猜一下我现在心里想的是哪个数字：")
    guess = int(temp)
    if guess == secret:
        print("我草，你是小曲心里的蛔虫吗？！")
        print("哼，猜中了也没有奖励！")
    else:
        if guess > secret:
            print("哥，大了，大了~~~")
        else:
            print("嘿，小了，小了~~~")
print("游戏结束，不玩啦^_^")
