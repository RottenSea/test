# 李欣晨 072440632


class Student:
    def __init__(self):
        self.name = "李明"
        self.__id = "072440632"

    def abc(self):
        print("姓名: %s, 学号: %s" % (self.name, self.__id))


stu = Student()
stu.abc()

stu.age = 20
print("姓名: %s, 年龄: %d" % (stu.name, stu.age))
