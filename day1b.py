with open("day1.txt") as fichier:
    l1 = []
    l2 = []
    dict = {}
    for i in range(1000):
        valeurs = fichier.readline().split("   ")
        l1.append(int(valeurs[0]))
        if int(valeurs[1]) in dict:
            dict[int(valeurs[1])] += 1
        else:
            dict[int(valeurs[1])] = 1
    total = 0
    print(dict)
    for i in l1:
        if i in dict:
            total += i * dict[i]
print(total)