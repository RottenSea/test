class Student:
    def __init__(self, name: str, student_id: str, age: int):
        self.name = name
        self.student_id = student_id
        self.age = age

    def show_id(self) -> str:
        return self.student_id

    def show_age(self) -> int:
        return self.age


# 示例：创建一个学生对象并以表格形式打印
stu = Student("张三", "20260101", 20)

header = f"{'姓名':<8}{'学号':<12}{'年龄':<4}"
row = f"{stu.name:<8}{stu.show_id():<12}{stu.show_age():<4}"

print(header)
print("-" * len(header))
print(row)
