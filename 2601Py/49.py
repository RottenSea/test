# 将一个文件夹的所有文件改为.md后缀

import os

# 修改为你的文件夹路径
folder_path = r"C:\Users\RottenTh\Desktop\Astro"

# 获取文件夹下所有文件
files = os.listdir(folder_path)

for file in files:
    # 获取文件名和后缀
    file_name, file_ext = os.path.splitext(file)

    # 排除已经是 .md 的文件以及文件夹
    if file_ext.lower() != ".md" and os.path.isfile(os.path.join(folder_path, file)):
        old_path = os.path.join(folder_path, file)
        new_path = os.path.join(folder_path, file_name + ".md")

        try:
            os.rename(old_path, new_path)
            print(f"已重命名: {file} -> {file_name}.md")
        except Exception as e:
            print(f"重命名 {file} 失败: {e}")

print("转换完成！")
