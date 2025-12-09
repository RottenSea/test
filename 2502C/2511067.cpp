#include <stdio.h>
#define MAXN 1000
int deque[MAXN];          // 双端队列，存下标
int front = 0, rear = -1; // 队头和队尾指针
void push_back(int index, int nums[])
{
    // 保证队列内元素对应的值递减
    while (rear >= front && nums[deque[rear]] <= nums[index])
        rear--;
    deque[++rear] = index;
}
void pop_front(int index, int k)
{
    // 如果队头已不在窗口范围内，弹出
    if (deque[front] <= index - k)
        front++;
}
int main()
{
    int nums[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int n = sizeof(nums) / sizeof(nums[0]);
    int k = 3;
    printf("数组: ");
    for (int i = 0; i < n; i++)
        printf("%d ", nums[i]);
    printf("\n窗口大小 k = %d\n", k);
    printf("滑动窗口最大值序列: ");
    for (int i = 0; i < n; i++)
    {
        push_back(i, nums); // 新元素入队
        pop_front(i, k);    // 移除不在窗口范围内的下标
        if (i >= k - 1)     // 从第k个元素开始输出结果
            printf("%d ", nums[deque[front]]);
    }
    printf("\n");
    return 0;
}
