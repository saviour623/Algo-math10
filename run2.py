from math import floor, ceil 
oo = 0
b2 = 0.3010299956639811952
while (oo < 5096):
    # n * 209 / 299 + 0.5 ≈ log10(x^n)
    print(len(str(5**oo)), floor(((oo * 0.69897000433602) + 0.5) + 0.5))
    oo += 1
print()

#digits(0) = x ^ n
#|_ |5^n/10^(n·log5)| _|, nlog5^n = nlog5
