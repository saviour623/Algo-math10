
for i in range(50, 126):
    k = list(str(5 ** i))
    x = 0
    o = len(k)
    p = []
    print('{', end="")
    while o > -1:
        o -= 1
        p.append(k[o])
        if x > 3:
            x = 0
            p.reverse()
            for oo in p:
                print(oo, end="")
            print(end=", ")
            p.clear()
        else:
            x += 1
    if x < 5:
        p.reverse()
        for oo in p[1:]:
            print(oo, end="")
    print('}', end="")
    print()
