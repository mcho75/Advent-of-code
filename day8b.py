with open("day8.txt") as fichier:
    tab = fichier.readlines()
    dict = {}
    for i in range(len(tab)):
        for j in range(len(tab[0])):
            if (tab[i][j] != '.') and (tab[i][j] != '\n'):
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
                if pos2 != pos1:
                    dx = pos2[0] - pos1[0]
                    dy = pos2[1] - pos1[1]
                    x = pos2[0] + dx
                    y = pos2[1] + dy
                    while (x >= 0) and (x < len(tab)) and (y >= 0) and (y < len(tab[0])-1):
                        if not((x, y) in antennes):
                            antennes.append((x, y))
                        x += dx
                        y += dy
                    x = pos2[0] - dx
                    y = pos2[1] - dy
                    while (x >= 0) and (x < len(tab)) and (y >= 0) and (y < len(tab[0])-1):
                        if not((x, y) in antennes):
                            antennes.append((x, y))
                        x -= dx
                        y -= dy
    tab_str = []
    for i in range(len(tab)):
        tab_str.append("")
        for j in range(len(tab[0])-1):
            if (i, j) in antennes:
                tab_str[-1] = tab_str[-1] + "#"
            else:
                tab_str[-1] = tab_str[-1] + tab[i][j]
    for i in tab_str:
        print(i)
    print(len(antennes))