import re
import math

text = input("Text: ")


words = re.findall(r"\b\w+(?:['-]\w+)*\b", text)
letters = sum(1 for c in text if c.isalpha())
sentences = re.findall(r'[.!?]', text)
lengthw = len(words)
lengths = len(sentences)


wcounter = 0

tlength = 0


L = (letters / lengthw) * 100
S = (lengths / lengthw) * 100


index = 0.0588 * L - 0.296 * S - 15.8

grade_level = round(index)


if grade_level < 1:
    print("Before Grade 1")
elif grade_level > 16:
    print("Grade 16+")
else:
    print(f"Grade {grade_level}")
