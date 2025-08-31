# 1176 et 1888 - 1178

with open("day5.txt") as fichier:
    qui_est_apres = [[] for i in range(100)]
    qui_est_avant = [[] for i in range(100)]
    for i in range(21):
        valeurs = fichier.readline().split("|")
        v1 = int(valeurs[0])
        v2 = int(valeurs[1])
        qui_est_apres[v1].append(v2)
        qui_est_avant[v2].append(v1)
    fichier.readline()
    total = 0
    for i in range(29-23):
        impression = fichier.readline().split(",")
        valide = True
        for j in range(len(impression)):
            for k in range(j+1, len(impression)):
                n1 = int(impression[j])
                n2 = int(impression[k])
                if (n2 in qui_est_avant[n1]) or (n1 in qui_est_apres[n2]):
                    valide = False
        if not(valide):
            print(impression)
            total += int(impression[len(impression)//2])
    print(total)