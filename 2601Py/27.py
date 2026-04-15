text = "one, two, thre; 1, 2, 3。!！"

for ch in [",", ";", "。", ".", "!", "！"]:
    text = text.replace(ch, "\n")

lines = [line.strip() for line in text.split("\n") if line.strip()]

print("\n".join(lines))
