with open("day9.txt") as fichier:
    ligne = fichier.readline()

class maillon():

    def __init__(self, id_objet, taille):
        self.id_objet = id_objet
        self.taille = taille

id_objet = 0
memoire = []
for i in range(len(ligne)):
    taille_objet = int(ligne[i])
    if i % 2 == 0:
        memoire.append([id_objet, taille_objet])
        id_objet += 1
    else:
        memoire.append([-1, taille_objet])
print(memoire)