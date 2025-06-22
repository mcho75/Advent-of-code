# + que 634

with open("day2.txt") as fichier:
    total = 0
    for i in range(1000):
        valeurs = fichier.readline().split(" ")
        print("\n\n", valeurs)
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
        else:
            for k in range(len(valeurs)):
                fonctionne_partiel = True
                temp = valeurs.pop(k)
                print("   ", valeurs)
                croissant = int(valeurs[0]) < int(valeurs[1])
                for j in range(len(valeurs)-1):
                    v = int(valeurs[j]) - int(valeurs[j+1])
                    if croissant:
                        v = -v
                    if (v <= 0) or (v >= 4):
                        fonctionne_partiel = False
                        print("       Probleme quand j =", j)
                valeurs.insert(k, temp)
                if fonctionne_partiel:
                    fonctionne = True
            if fonctionne:
                total += 1
print(total)