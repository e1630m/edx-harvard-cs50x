h = -1
while not (0 < h < 9):
    try:
        h = int(input('Height: '))
    except ValueError:
        h = -1
for i in range(h):
    l = ' ' * (h - i - 1) + '#' * (i + 1)
    print(f'{l}  {"#" * (i + 1)}')