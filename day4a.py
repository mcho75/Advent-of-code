# 2370 too high

positions = [[(-1, 0), (-2, 0), (-3, 0)],
             [(0, -1), (0, -2), (0, -3)],
             [(1, 0), (2, 0), (3, 0)],
             [(0, 1), (0, 2), (0, 3)],
             [(-1, -1), (-2, -2), (-3, -3)],
             [(-1, 1), (-2, 2), (-3, 3)],
             [(1, -1), (2, -2), (3, -3)],
             [(1, 1), (2, 2), (3, 3)]]
texte = ['M', 'A', 'S']

with open("day4.txt") as fichier:
    matrice = []
    total = 0
    valide = True
    for i in range(140):
        matrice.append(fichier.readline())
    for i in range(len(matrice)):
        for j in range(len(matrice[0])-1):
            if matrice[i][j] == 'X':
                for pos in positions:
                    valide = True
                    for lettre in range(3):
                        if i+pos[lettre][0] >= 0 and j+pos[lettre][1] >= 0:
                            try:
                                if matrice[i+pos[lettre][0]][j+pos[lettre][1]] != texte[lettre]:
                                    valide = False
                            except:
                                valide = False
                        else:
                            valide = False
                    if valide:
                        print("Trouvé en", i, j, "avec", pos)
                        total += 1
    print(total)