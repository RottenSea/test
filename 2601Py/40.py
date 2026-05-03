# 李欣晨 072440632


class Car:
    brand = "未知品牌"
    color = "未知颜色"


car1 = Car()
car2 = Car()


car1.brand = "比亚迪"
print('Car类: brand="%s", color="%s"' % (Car.brand, Car.color))
print('car1: brand="%s", color="%s"' % (car1.brand, car1.color))
print('car2: brand="%s", color="%s"' % (car2.brand, car2.color))
car1.color = "白色"
print('Car类: brand="%s", color="%s"' % (Car.brand, Car.color))
print('car1: brand="%s", color="%s"' % (car1.brand, car1.color))
print('car2: brand="%s", color="%s"' % (car2.brand, car2.color))
