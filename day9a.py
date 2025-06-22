# ajout de 0 a la fin du fichier

with open("day9.txt") as fichier:
    ligne = fichier.readline()

id_objet = 0
memoire = []
cases_vides = []
for i in range(len(ligne)//2):
    taille_objet = int(ligne[2*i])
    for j in range(taille_objet):
        memoire.append(id_objet)
    taille_vide = int(ligne[2*i+1])
    for j in range(taille_vide):
        memoire.append(-1)
        cases_vides.append(len(memoire)-1)
    id_objet += 1
if len(ligne) % 2 == 1:
    taille_objet = int(ligne[-1])
    for j in range(taille_objet):
        memoire.append(id_objet)
print(memoire)

case = len(memoire) - 1
while case > cases_vides[0]:
    while memoire[case] == -1:
        case -= 1
    memoire[cases_vides[0]] = memoire[case]
    memoire[case] = -1
    cases_vides.pop(0)
    cases_vides.append(case)
print(memoire)

total = 0
i = 0
while memoire[i] != -1:
    total += i * memoire[i]
    i += 1
print(total)