coins = (25, 10, 5, 1)
while 1:
    try:
        owed = float(input('Change owed: '))
        if owed >= 0 and round(owed, 2) == round(owed, 3):
            break
    except ValueError:
        pass
owed *= 100
num_changes = 0
while owed > 0:
    owed -= 25 if owed >= 25 else 10 if owed >= 10 \
        else 5 if owed >= 5 else 1
    num_changes += 1
print(num_changes)
