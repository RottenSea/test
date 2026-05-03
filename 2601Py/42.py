class Student:
    def __init__(self, name="未知"):
        self.name = name
        print("姓名为%s的对象被创建!" % self.name)

    def __del__(self):
        print("姓名为%s的对象被析构!" % self.name)

    def SetInfo(self, newname):
        self.name = newname

    def PrintInfo(self):
        print("姓名" % self.name)


def func(name):
    stu = Student(name)


stu1 = Student("李晓明")
stu2 = Student("马红")
stu3 = stu2
del stu2
func("张刚")
del stu3
stu4 = Student("刘建")
