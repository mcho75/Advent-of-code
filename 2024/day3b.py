# ((mul\(\d{1,3},\d{1,3}\)|don't\(\))|do\(\))

total = 0
with open("day3_extraction2.txt") as fichier:
    actif = True
    for i in range(746):
        ligne = fichier.readline().split(" ")
        if len(ligne) == 1:
            if len(ligne[0]) == 4:    # do
                actif = True
            if len(ligne[0]) == 7:    # don't
                actif = False
        elif actif:
            total += int(ligne[0]) * int(ligne[1])
print(total)