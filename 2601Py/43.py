# 李欣晨 072440632


class Student:
    def __init__(self, name, id):
        self.name = name
        self.id = id

    def learn(self):
        print("学生%s学号%s在进行操作" % (self.name, self.id))


class Teacher:
    def __init__(self, name, id):
        self.name = name
        self.id = id

    def teach(self):
        print("教师%s工号%s在进行授课" % (self.name, self.id))


stu = Student("李明", "072440632")
tea = Teacher("张老师", "T001")

print("学生姓名: %s, 学号: %s" % (stu.name, stu.id))
stu.learn()

print("教师姓名: %s, 工号: %s" % (tea.name, tea.id))
tea.teach()
