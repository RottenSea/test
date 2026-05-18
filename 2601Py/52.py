import os
import sys
from fontTools.ttLib import TTFont

downloads = os.path.expanduser("~/Downloads")

family_files = {}
for root, dirs, files in os.walk(downloads):
    for f in files:
        if f.lower().endswith((".ttf", ".otf")):
            parent = os.path.basename(root)
            if parent == "static":
                parent = os.path.basename(os.path.dirname(root))
            family_files.setdefault(parent, []).append(os.path.join(root, f))

if not family_files:
    print("No font files found in Downloads", flush=True)
    sys.exit(0)

total_ok = 0
total_fail = 0

for family, paths in sorted(family_files.items()):
    out_dir = os.path.join(downloads, f"{family}_woff2")
    os.makedirs(out_dir, exist_ok=True)
    print(f"[{family}] ({len(paths)} files) -> {out_dir}", flush=True)

    for src in sorted(paths):
        name = os.path.splitext(os.path.basename(src))[0] + ".woff2"
        dst = os.path.join(out_dir, name)
        try:
            font = TTFont(src)
            font.flavor = "woff2"
            font.save(dst)
            font.close()
            sz = os.path.getsize(dst)
            print(f"  OK  {os.path.basename(src)} -> {sz:,} bytes", flush=True)
            total_ok += 1
        except Exception as e:
            print(f"  FAIL {os.path.basename(src)}: {e}", flush=True)
            total_fail += 1

    print(flush=True)

print(f"Done: {total_ok} converted, {total_fail} failed", flush=True)
