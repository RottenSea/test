class MemoryBlock:
    def __init__(self, size):
        self.size = size
        self.free = True

    def __repr__(self):
        status = "Free" if self.free else "Used"
        return f"[{self.size}KB, {status}]"


class BestFitAllocator:
    def __init__(self, blocks):
        # 初始化内存块
        self.blocks = [MemoryBlock(size) for size in blocks]

    def allocate(self, request_size):
        best_index = -1
        min_remaining = float("inf")

        # 查找最佳适应块
        for i, block in enumerate(self.blocks):
            if block.free and block.size >= request_size:
                remaining = block.size - request_size

                if remaining < min_remaining:
                    min_remaining = remaining
                    best_index = i

        # 找不到合适块
        if best_index == -1:
            print(f"申请 {request_size}KB 失败：内存不足")
            return False

        # 分配内存
        block = self.blocks[best_index]

        print(f"申请 {request_size}KB")
        print(f"使用分区: {block.size}KB")

        remaining_size = block.size - request_size

        # 当前块变为已使用
        block.size = request_size
        block.free = False

        # 如果有剩余空间，创建新空闲块
        if remaining_size > 0:
            new_block = MemoryBlock(remaining_size)

            self.blocks.insert(best_index + 1, new_block)

        return True

    def show_memory(self):
        print("\n当前内存状态：")
        for i, block in enumerate(self.blocks):
            print(f"分区{i}: {block}")


# ======================
# 测试
# ======================

memory_sizes = [100, 500, 200, 300, 600]

allocator = BestFitAllocator(memory_sizes)

allocator.show_memory()

# 模拟进程申请
allocator.allocate(212)

allocator.show_memory()

allocator.allocate(100)

allocator.show_memory()

allocator.allocate(417)

allocator.show_memory()
