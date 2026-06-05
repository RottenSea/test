from pypdf import PdfReader

reader = PdfReader("input.pdf")
text = "\n".join([page.extract_text() for page in reader.pages])

with open("output.txt", "w", encoding="utf-8") as f:
    f.write(text)
