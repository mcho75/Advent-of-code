possibles = [('M', 'M', 'S', 'S'),
             ('M', 'S', 'M', 'S'),
             ('S', 'M', 'S', 'M'),
             ('S', 'S', 'M', 'M')]

with open("day4.txt") as fichier:
    matrice = []
    total = 0
    valide = True
    for i in range(140):
        matrice.append(fichier.readline())
    for i in range(1, len(matrice)-1):
        for j in range(1, len(matrice[0])-2):
            if matrice[i][j] == 'A':
                lettres = (matrice[i-1][j-1], matrice[i-1][j+1], matrice[i+1][j-1], matrice[i+1][j+1])
                if lettres in possibles:
                    print(i, j)
                    total += 1
    print(total)