# 1176 et 1389 - 1178

# 3106 : trop peu

with open("day5.txt") as fichier:
    matrice_avant = [[False for i in range(100)] for j in range(100)]
    temp = [[False for i in range(100)] for j in range(100)]
    for i in range(1176):
        valeurs = fichier.readline().split("|")
        v1 = int(valeurs[0])
        v2 = int(valeurs[1])
        matrice_avant[v2][v1] = True
        temp[v2][v1] = True
    fichier.readline()
    total = 0
    for i in range(1389-1178):
        impression = fichier.readline().split(",")
        valide = True
        for j in range(len(impression)):
            for k in range(j+1, len(impression)):
                n1 = int(impression[j])
                n2 = int(impression[k])
                if matrice_avant[n1][n2]:
                    valide = False
        if not valide:
            impr = []
            nouvelle = []
            for i in impression:
                impr.append(int(i))
            print(impr)
            tailles = [0 for i in range(len(matrice_avant))]
            for i in impr:
                for j in impr:
                    if (i != j) and matrice_avant[i][j]:
                        tailles[i] += 1
            while len(impr) != 0:
                a_supprimer = []
                i = 0
                while i < len(impr):
                    if tailles[impr[i]] == 0:
                        print("rien avant", impr[i])
                        for j in range(len(tailles)):
                            if tailles[j] != 0:
                                print("  ", j, ":", tailles[j])
                        nouvelle.append(impr[i])
                        a_supprimer.append(impr[i])
                        impr.pop(i)
                        i -= 1
                    i += 1
                for ref in a_supprimer:
                    for i in impr:
                        if (i != ref) and matrice_avant[i][ref]:
                            tailles[i] -= 1
            print(nouvelle)
            print()
            total += nouvelle[len(nouvelle)//2]

            for j in range(len(nouvelle)):
                for k in range(j+1, len(nouvelle)):
                    n1 = int(nouvelle[j])
                    n2 = int(nouvelle[k])
                    if temp[n1][n2]:
                        print(n1, n2)
    print(total)