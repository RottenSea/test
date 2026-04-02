user = {"name": "zhang", "age": 30, "xuehao": "07"}
for k, v in user.items():
    if v == 30:
        print()
    print("-------------")


for i in user.keys():
    if i == "age":
        print(user["age"])
    print(i)
print("------------")

for j in user.values():
    if j == 30:
        print()
    print(j)
print("-----------")

# l = [1,2,3,4]
# d = {}
# print(d.fromkeys(l,0))

# d1 = {1: "11", 2: "22", 3: "33"}
# print(d1.get(2, "0.0"))
# print(d1.get(4, "0.0"))
# print(d1)
# print("--------------")
# print(d1.setdefault(3, "0*0"))
# print(d1)
# print(d1.setdefault(4, "0*0"))
# print(d1)

# lst = [1, 2, 3, 4, 5]
# lst1 = reversed(lst)
# print(list(lst1))
# print(lst)
# print(lst1)
# print(list(lst1))
# print(list(lst1))

# lst.reserse()
# print(lst)

# list1 = [1, 2, 3, 4]
# list2 = [5, 6, 7, 8]
# z1 = zip(list1, list2)
# print(z1)
# i, j = zip(*z1)
# print(i, j)

# my_list = [3,5,1,4,2]
# print(id(my_list))
# my_list.sort()
# print(id(my_list))
# print(my_list)






