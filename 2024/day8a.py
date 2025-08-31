# 230 : too high

with open("day8.txt") as fichier:
    tab = fichier.readlines()
    dict = {}
    for i in range(len(tab)):
        for j in range(len(tab[0])):
            if tab[i][j] != '.':
                if tab[i][j] in dict.keys():
                    dict[tab[i][j]].append((i, j))
                else:
                    dict[tab[i][j]] = [(i, j)]
    antennes = []
    print(dict)
    for key in dict.keys():
        liste_pos = dict[key]
        for pos1 in liste_pos:
            for pos2 in liste_pos:
                x = 2 * pos2[0] - pos1[0]
                y = 2 * pos2[1] - pos1[1]
                if (x >= 0) and (x < len(tab)) and (y >= 0) and (y < len(tab[0])-1):
                    if (tab[x][y] != key) and not((x, y) in antennes):
                        antennes.append((x, y))
                x = 2 * pos1[0] - pos2[0]
                y = 2 * pos1[1] - pos2[1]
                if (x >= 0) and (x < len(tab)) and (y >= 0) and (y < len(tab[0])-1):
                    if (tab[x][y] != key) and not((x, y) in antennes):
                        antennes.append((x, y))
    tab_str = []
    for i in range(len(tab)):
        tab_str.append("")
        for j in range(len(tab[0])-1):
            est_dedans = (i, j) in antennes
            if est_dedans:
                tab_str[-1] = tab_str[-1] + "#"
            else:
                tab_str[-1] = tab_str[-1] + tab[i][j]
    for i in tab_str:
        print(i)
    print(len(antennes))