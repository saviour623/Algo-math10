n = 0.000000000000000000004678
i = 0
while (i < 308):
    n = n * 2
    if (n >= 1.0):
        n -= 1
        print(1, end="")
    else:
        print(0, end="")
    i = i + 1
