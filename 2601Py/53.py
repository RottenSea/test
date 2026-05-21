import os
from pypdf import PdfReader, PdfWriter

downloads = os.path.expanduser("~/Downloads")
pdf_name = "平凡的真理 (冯定著) (z-library.sk, 1lib.sk, z-lib.sk).pdf"
pdf_path = os.path.join(downloads, pdf_name)

out_dir = os.path.join(downloads, "平凡的真理_split")
os.makedirs(out_dir, exist_ok=True)

reader = PdfReader(pdf_path)
total = len(reader.pages)

step = 30
for start in range(0, total, step):
    end = min(start + step, total)
    writer = PdfWriter()
    for i in range(start, end):
        writer.add_page(reader.pages[i])
    out_name = f"平凡的真理_{start+1:03d}-{end:03d}.pdf"
    out_path = os.path.join(out_dir, out_name)
    writer.write(out_path)
    writer.close()
    print(f"  {out_name} ({end-start} pages)", flush=True)

print(f"Done: {total} pages -> {out_dir}")
