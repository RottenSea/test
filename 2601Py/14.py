for cock in range(1, 20):
    for hen in range(1, 33):
        chick = 100 - cock - hen
        if chick > 0 and 5 * cock + 3 * hen + chick / 3 == 100:
            print(f"公鸡: {cock} 只, 母鸡: {hen} 只, 小鸡: {chick} 只")
