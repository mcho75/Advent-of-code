COUT_A = 3
COUT_B = 1

total = 0

def divise(num, denom):
    return denom * (num // denom) == num

with open("day13_extraction.txt") as fichier:
    for i in range(320):
        boutonA = fichier.readline().split(" ")
        boutonB = fichier.readline().split(" ")
        pos_prix = fichier.readline().split(" ")
        fichier.readline()
        print(boutonA, boutonB, pos_prix)
        xA = int(boutonA[0])
        yA = int(boutonA[1])
        xB = int(boutonB[0])
        yB = int(boutonB[1])
        px = int(pos_prix[0]) + 10000000000000
        py = int(pos_prix[1]) + 10000000000000
        det = (xA * yB) - (xB * yA)
        numA = (yB * px) - (xB * py)
        numB = (xA * py) - (yA * px)
        if divise(numA, det) and divise(numB, det):
            total += (COUT_A * numA // det) + (COUT_B * numB // det)
print(total)