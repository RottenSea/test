import os

# 修改为你的视频文件夹路径
folder_path = r"C:\Users\RottenTh\Videos\wechat"

# 获取所有 mp4 文件并排序
files = sorted([f for f in os.listdir(folder_path) if f.lower().endswith(".mp4")])

# 先临时重命名，避免文件名冲突
for i, file in enumerate(files):
    old_path = os.path.join(folder_path, file)
    temp_path = os.path.join(folder_path, f"temp_{i}.mp4")
    os.rename(old_path, temp_path)

# 再正式重命名
temp_files = sorted(
    [f for f in os.listdir(folder_path) if f.startswith("temp_") and f.endswith(".mp4")]
)

for i, file in enumerate(temp_files):
    old_path = os.path.join(folder_path, file)
    new_name = f"{i:03d}.mp4"  # 000, 001, 002...
    new_path = os.path.join(folder_path, new_name)
    os.rename(old_path, new_path)

print("重命名完成！")
