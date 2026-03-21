for i in range(1, 10):
    for j in range(i, 0, -1):
        print(f"{j}*{i}={i*j}", end="\t")
    print()
