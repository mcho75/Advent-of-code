with open("day1.txt") as fichier:
    l1 = []
    l2 = []
    for i in range(1000):
        valeurs = fichier.readline().split("   ")
        l1.append(int(valeurs[0]))
        l2.append(int(valeurs[1]))
    l1.sort()
    l2.sort()
    total = 0
    while len(l1) > 0:
        total += abs(l1[0] - l2[0])
        l1.pop(0)
        l2.pop(0)
print(total)