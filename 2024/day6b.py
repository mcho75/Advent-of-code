# exemple : 10, (6, 4)
# perso : 130, (90, 91)

with open("day6.txt") as fichier:

    valeurs = [130, 90, 91]
    # valeurs = [10, 6, 4]

    tab = []
    for i in range(valeurs[0]):
        tab.append([])
        ligne = fichier.readline()
        for j in ligne:
            tab[i].append([0, -1][j == "#"])
    cases_explorees = []

    # liste les cases explorees
    direction = 0
    guard = [valeurs[1], valeurs[2]]
    tab[guard[0]][guard[1]] = 0
    ne_sort_pas = True
    while ne_sort_pas:
        while ne_sort_pas and (tab[guard[0]][guard[1]] != -1):
            cases_explorees.append([guard[0], guard[1], direction])
            if direction == 0: guard[0] -= 1
            if direction == 1: guard[1] += 1
            if direction == 2: guard[0] += 1
            if direction == 3: guard[1] -= 1
            if (guard[0] < 0) or (guard[0] >= len(tab)) or (guard[1] < 0) or (guard[1] >= len(tab[0])):
                ne_sort_pas = False
        if direction == 0: guard[0] += 1
        if direction == 1: guard[1] -= 1
        if direction == 2: guard[0] -= 1
        if direction == 3: guard[1] += 1
        direction = (direction + 1) % 4

    # liste des boites que l'on peut ajouter
    a_ajouter = []
    for explore in cases_explorees:
        if explore[2] == 0: nouveau = [explore[0]-1, explore[1]]
        if explore[2] == 1: nouveau = [explore[0], explore[1]+1]
        if explore[2] == 2: nouveau = [explore[0]+1, explore[1]]
        if explore[2] == 3: nouveau = [explore[0], explore[1]-1]
        if (nouveau[0] >= 0) and (nouveau[0] < len(tab)) and (nouveau[1] >= 0) and (nouveau[1] < len(tab[0])):
            if (not nouveau in a_ajouter) and (tab[nouveau[0]][nouveau[1]] != -1):
                a_ajouter.append(nouveau)
    print(a_ajouter)

    total = 0
    for ajoute in a_ajouter:
        print("Ajout d'une boite en", ajoute[0], ajoute[1])
        tab[ajoute[0]][ajoute[1]] = -1
        direction = 0
        guard = [valeurs[1], valeurs[2]]
        ne_sort_pas = True
        pas_encore_boucle = True
        obstacles_rencontres = []
        while ne_sort_pas and pas_encore_boucle:
            while ne_sort_pas and (tab[guard[0]][guard[1]] != -1):
                if direction == 0: guard[0] -= 1
                if direction == 1: guard[1] += 1
                if direction == 2: guard[0] += 1
                if direction == 3: guard[1] -= 1
                if (guard[0] < 0) or (guard[0] >= len(tab)) or (guard[1] < 0) or (guard[1] >= len(tab[0])):
                    ne_sort_pas = False
            if ne_sort_pas:
                if [guard[0], guard[1], direction] in obstacles_rencontres:
                    pas_encore_boucle = False
                obstacles_rencontres.append([guard[0], guard[1], direction])
            if direction == 0: guard[0] += 1
            if direction == 1: guard[1] -= 1
            if direction == 2: guard[0] -= 1
            if direction == 3: guard[1] += 1
            direction = (direction + 1) % 4
        if not pas_encore_boucle:
            print(obstacles_rencontres[-1])
            total += 1
        tab[ajoute[0]][ajoute[1]] = 0

    tab_str = []
    for i in tab:
        tab_str.append("")
        for j in i:
            tab_str[-1] = tab_str[-1] + [".", "X", "#"][j]
    for i in tab_str:
        print(i)
    print(total)