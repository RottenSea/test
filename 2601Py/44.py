# 李欣晨 072440632


class Person:
    def __init__(self, name, weight):
        self.name = name
        self.weight = weight

    def run(self):
        self.weight -= 0.5
        print("%s跑步了，体重变为 %.1fKG" % (self.name, self.weight))

    def eat(self):
        self.weight += 1.0
        print("%s吃饭了，体重变为 %.1fKG" % (self.name, self.weight))


xiaoming = Person("小明", 100.0)
print("%s的初始体重为 %.1fKG" % (xiaoming.name, xiaoming.weight))

xiaoming.run()
xiaoming.eat()
xiaoming.run()
