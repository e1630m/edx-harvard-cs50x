letters = words = sentences = 0
for c in input('Text: '):
    if c in '.!?':
        sentences += 1
    elif c == ' ':
        words += 1
    elif c.isalpha():
        letters += 1
words += 1
grade = round((5.88 * letters - 29.6 * sentences) / words - 15.8)
print(f'Before Grade 1' if grade < 1 else 'Grade 16+' if grade >= 16 else f'Grade {grade}')
