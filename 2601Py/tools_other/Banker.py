class BankersAlgorithm:
    def __init__(self, available, max_demand, allocation):
        self.available = available[:]  # 可用资源
        self.max_demand = max_demand
        self.allocation = allocation
        self.process_num = len(max_demand)
        self.resource_num = len(available)
        self.need = [
            [self.max_demand[i][j] - self.allocation[i][j] for j in range(self.resource_num)]
            for i in range(self.process_num)
        ]

    def is_safe(self):
        work = self.available[:]
        finish = [False] * self.process_num
        safe_sequence = []

        while len(safe_sequence) < self.process_num:
            found = False
            for i in range(self.process_num):
                if not finish[i] and all(self.need[i][j] <= work[j] for j in range(self.resource_num)):
                    # 假装执行完成
                    for j in range(self.resource_num):
                        work[j] += self.allocation[i][j]
                    finish[i] = True
                    safe_sequence.append(f"P{i}")
                    found = True
            if not found:
                return False, []
        return True, safe_sequence

    def request_resources(self, pid, request):
        print(f"\n进程 P{pid} 请求资源: {request}")

        # Step 1: 请求不能超过需求
        if any(request[j] > self.need[pid][j] for j in range(self.resource_num)):
            print("错误：请求超过进程最大需求！")
            return False

        # Step 2: 请求不能超过可用资源
        if any(request[j] > self.available[j] for j in range(self.resource_num)):
            print("资源不足，进程必须等待。")
            return False

        # Step 3: 假设分配后检查安全性
        # 临时分配
        for j in range(self.resource_num):
            self.available[j] -= request[j]
            self.allocation[pid][j] += request[j]
            self.need[pid][j] -= request[j]

        safe, sequence = self.is_safe()

        if safe:
            print("分配成功，系统仍然安全。")
            print("安全序列:", " -> ".join(sequence))
            return True
        else:
            # 回滚
            for j in range(self.resource_num):
                self.available[j] += request[j]
                self.allocation[pid][j] -= request[j]
                self.need[pid][j] += request[j]
            print("分配失败，系统将进入不安全状态，进程等待。")
            return False

    def show_state(self):
        print("\n当前系统状态：")
        print("Available:", self.available)
        print("Allocation:", self.allocation)
        print("Need:", self.need)


# =======================
# 测试数据
# =======================
available = [3, 3, 2]

max_demand = [
    [7, 5, 3],
    [3, 2, 2],
    [9, 0, 2],
    [2, 2, 2],
    [4, 3, 3]
]

allocation = [
    [0, 1, 0],
    [2, 0, 0],
    [3, 0, 2],
    [2, 1, 1],
    [0, 0, 2]
]

banker = BankersAlgorithm(available, max_demand, allocation)

banker.show_state()

# 进程 P1 请求 [1, 0, 2]
banker.request_resources(1, [1, 0, 2])
banker.show_state()

# 进程 P4 请求 [3, 3, 0]
banker.request_resources(4, [3, 3, 0])
banker.show_state()