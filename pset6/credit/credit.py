def luhn(cc):
    odd, even = 0, 0
    for i, c in enumerate(cc[::-1]):
        if i % 2 == 0:
            odd += int(c)
        else:
            q, r = divmod(int(c) * 2, 10)
            even += q + r
    return not ((even + odd) % 10)


def network(cc):
    if cc.isdigit():
        if len(cc) == 16 and cc[0] == '5' and cc[1] in '12345':
            return 'MASTERCARD'
        elif len(cc) == 15 and cc[0] == '3' and cc[1] in '47':
            return 'AMEX'
        elif len(cc) in (13, 16) and cc[0] == '4':
            return 'VISA'
    return 'INVALID'


cc = ''
while not (network(cc).isdigit()) and len(cc) < 10:
    cc = input('Number: ')
print(network(cc) if luhn(cc) else 'INVALID')
