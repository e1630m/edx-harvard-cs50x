h = -1
while not (0 < h < 9):
    try:
        h = int(input('Height: '))
        m = h + 1
    except ValueError:
        h = -1
print(''.join(("#" * i).rjust(h, " ") + "\n" * (i < h) for i in range(1, m)))
