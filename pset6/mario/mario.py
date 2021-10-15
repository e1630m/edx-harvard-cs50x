h = -1
while not (0 < h < 9):
    try:
        h = int(input('Height: '))
    except ValueError:
        h = -1
for i in range(1, h + 1):
    print(f'{("#" * i).rjust(h, " ")}  {"#" * i}')
