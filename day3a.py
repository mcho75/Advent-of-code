# 156788121 : trop grand
# mul\(\d{1,3},\d{1,3}\)

"""
with open("day3.txt") as fichier:
    total = 0
    for i in range(6):
        ligne = fichier.readline().split("mul(")
        ligne.pop(0)
        for j in ligne:
            j_separe = j.split(",")
            try:
                v1 = int(j_separe[0])
                v2 = int(j_separe[1].split(")")[0])
                total += v1*v2
                print(v1, v2, total)
            except:
                pass
print(total)
"""

total = 0
with open("day3_extraction.txt") as fichier:
    for i in range(678):
        valeurs = fichier.readline().split(" ")
        print(int(valeurs[0]), int(valeurs[1]))
        total += int(valeurs[0]) * int(valeurs[1])
print(total)