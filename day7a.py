def tester_rec(calcul, nb_restants, a_atteindre):
    if len(nb_restants) == 0:
        if calcul == a_atteindre:
            return 1
        return 0
    if calcul > a_atteindre:
        return 0
    nb = nb_restants[0]
    return tester_rec(calcul+nb, nb_restants[1:], a_atteindre) + tester_rec(calcul*nb, nb_restants[1:], a_atteindre)

with open("day7.txt") as fichier:
    total = 0
    for i in range(850):
        ligne = fichier.readline().split(": ")
        valeur_test = int(ligne[0])
        nombres = [int(i) for i in ligne[1].split(" ")]
        resultat = tester_rec(nombres[0], nombres[1:], valeur_test)
        if resultat != 0:
            total += valeur_test
        print(valeur_test, nombres, resultat)
    print(total)