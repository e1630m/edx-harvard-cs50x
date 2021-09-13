import os
import sys


def rr(path: str) -> list:
    with open(path, 'r') as f:
        data = f.readlines()
    return data


def csv_reader(path: str, data={}) -> dict:
    csv = rr(path)
    title = [c.strip('\n') for c in csv[0].split(',')]
    for line in csv[1:]:
        line = line.split(',')
        data[line[0]] = {t: int(d.strip('\n')) for t, d in zip(title[1:], line[1:])}
    return data, title[1:]


def counter(path: str, target, data={}) -> dict:
    dna = rr(path)[0]
    len_d = len(dna)
    for k in target:
        i = tmp = longest = 0
        len_k = len(k)
        limit = len_d - len_k + 1
        while i < limit:
            if dna[i:i + len_k] == k:
                i += len_k
                tmp += 1
                longest = max(longest, tmp)
            else:
                i += 1
                tmp = 0
        data[k] = longest
    return data


if len(sys.argv) != 3:
    sys.exit('Usage: python dna.py data.csv sequence.txt')
elif not os.path.isfile(sys.argv[1]) or not os.path.isfile(sys.argv[2]):
    sys.exit(f'Error: file not found')
db, target = csv_reader(sys.argv[1])
seq = counter(sys.argv[2], target)
matched = [k for k, v in db.items() if v == seq]
print(matched[0] if matched else 'No match')
