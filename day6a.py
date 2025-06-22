# exemple : 10, (6, 4)
# perso : 130, (90, 91)

with open("day6.txt") as fichier:
    tab = []
    for i in range(130):
        tab.append([])
        ligne = fichier.readline()
        for j in ligne:
            tab[i].append([0, -1][j == "#"])
    direction = 0
    # 0=haut ; 1=droite ; 2=bas ; 3=gauche
    guard = [90, 91]
    tab[guard[0]][guard[1]] = 0
    total = 0
    ne_sort_pas = True
    while ne_sort_pas:
        while ne_sort_pas and (tab[guard[0]][guard[1]] != -1):
            if tab[guard[0]][guard[1]] == 0:
                total += 1
            tab[guard[0]][guard[1]] = 1
            if direction == 0:
                guard[0] -= 1
            if direction == 1:
                guard[1] += 1
            if direction == 2:
                guard[0] += 1
            if direction == 3:
                guard[1] -= 1
            if (guard[0] < 0) or (guard[0] >= len(tab)) or (guard[1] < 0) or (guard[1] >= len(tab[0])):
                ne_sort_pas = False
            print(guard, direction)
        if direction == 0:
            guard[0] += 1
        if direction == 1:
            guard[1] -= 1
        if direction == 2:
            guard[0] -= 1
        if direction == 3:
            guard[1] += 1
        direction = (direction + 1) % 4
    tab_str = []
    for i in tab:
        tab_str.append("")
        for j in i:
            tab_str[-1] = tab_str[-1] + [".", "X", "#"][j]
    for i in tab_str:
        print(i)
    print(total)