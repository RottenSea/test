# 名字:李欣晨 072440632


def count_chars(s):
    digit_count = 0
    alpha_count = 0
    space_count = 0
    other_count = 0

    for i in s:
        if i.isdigit():
            digit_count += 1
        elif i.isalpha():
            alpha_count += 1
        elif i.isspace():
            space_count += 1
        else:
            other_count += 1

    return digit_count, alpha_count, space_count, other_count


res = count_chars("Python 3.12 is the latest version!")
print(res)
