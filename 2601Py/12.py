while True:
    temp = input("请输入一个数字（输入'结束'退出游戏）：")
    if temp == "结束":
        break

    try:
        num = int(temp)
        if num % 2 == 0:
            print(f"{num} 是偶数")
        else:
            print(f"{num} 是奇数")
    except ValueError:
        print("请输入有效的整数！")

print("游戏结束")
