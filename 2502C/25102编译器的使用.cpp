#include <stdio.h>

// 定义PI的值
#define PI 3.14159265358979323846

// 函数声明
double sphereVolume(double radius);
double celsiusToFahrenheit(double celsius);

int main()
{
    double radius, celsius;
    // 输入球的半径
    printf("请输入球的半径: ");
    scanf("%lf", &radius);
    // 计算球的体积
    double volume = sphereVolume(radius);
    printf("半径为 %.2lf 的球的体积是: %.2lf\n", radius, volume);
    // 输入摄氏度
    printf("请输入摄氏度: ");
    scanf("%lf", &celsius);
    // 转换并输出华氏度
    double fahrenheit = celsiusToFahrenheit(celsius);
    printf("%.2lf 摄氏度等于 %.2lf 华氏度\n", celsius, fahrenheit);
    return 0;
}

// 计算球的体积
double sphereVolume(double radius)
{
    return (4.0 / 3.0) * PI * radius * radius * radius;
}

// 摄氏度转华氏度
double celsiusToFahrenheit(double celsius)
{
    return (celsius * 9.0 / 5.0) + 32.0;
}