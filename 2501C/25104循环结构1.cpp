#include <stdio.h>

// 1.每个合数都可以写成几个质数相乘的形式，其中每个质数都是这个合数的因数，把一个合数用质因数相乘的形式表示出来，叫做分解质因数，也叫做分解质因子，如30=2*3*5 。请输入一个合数，将其表示为质因数相乘的形式。

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
}

int findPrime(int a)
{
    for (int i = 2; i <= a; i++)
    {
        if (a % i == 0)
        {
            return i;
        }
    }
}

int main()
{
    int composite, prime[999], pointer = 0, primeN;
    printf("Enter a composite number :");
    scanf("%d", &composite);
    while (composite > 1)
    {
        primeN = findPrime(composite);
        prime[pointer] = primeN;
        composite = composite / primeN;
        pointer += 1;
    }
    printf("Prime numbers of composite number are :");
    printArray(prime, pointer);
    return 0;
}