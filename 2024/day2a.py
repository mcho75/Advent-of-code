with open("day2.txt") as fichier:
    total = 0
    for i in range(1000):
        valeurs = fichier.readline().split(" ")
        croissant = int(valeurs[0]) < int(valeurs[1])
        fonctionne = True
        for j in range(len(valeurs)-1):
            v = int(valeurs[j]) - int(valeurs[j+1])
            if croissant:
                v = -v
            if (v <= 0) or (v >= 4):
                fonctionne = False
        if fonctionne:
            total += 1
print(total)