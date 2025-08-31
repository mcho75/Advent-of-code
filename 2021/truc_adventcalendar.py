def j1a():
    var = 0
    with open("adventcalendar_1.txt") as fichier:
        temp = int(fichier.readline())
        for i in range(2000 - 1):
            temp2 = int(fichier.readline())
            if temp2 > temp:
                var += 1
            temp = temp2
    print(var)


def j1b():
    var = 0
    with open("adventcalendar_1.txt") as fichier:
        temp1 = int(fichier.readline())
        temp2 = int(fichier.readline())
        temp3 = int(fichier.readline())
        for i in range(2000-3):
            somme = temp1 + temp2 + temp3
            temp1 = temp2
            temp2 = temp3
            temp3 = int(fichier.readline())
            if temp1 + temp2 + temp3 > somme:
                var += 1
    print(var)


def j2a():
    horizontal = 0
    depth = 0
    with open("adventcalendar_2.txt") as fichier:
        for i in range(1000):
            ligne = fichier.readline().split()
            if ligne[0] == "forward":
                horizontal += int(ligne[1])
            elif ligne[0] == "up":
                depth -= int(ligne[1])
            elif ligne[0] == "down":
                depth += int(ligne[1])
    print(horizontal * depth)


def j2b():
    horizontal = 0
    depth = 0
    aim = 0
    with open("adventcalendar_2.txt") as fichier:
        for i in range(1000):
            ligne = fichier.readline().split()
            if ligne[0] == "forward":
                horizontal += int(ligne[1])
                depth += aim * int(ligne[1])
            elif ligne[0] == "up":
                aim -= int(ligne[1])
            elif ligne[0] == "down":
                aim += int(ligne[1])
    print(horizontal * depth)


def j3a():
    presence_0 = [0 for i in range(12)]
    with open("adventcalendar_3.txt") as fichier:
        for i in range(1000):
            ligne = fichier.readline()
            for j in range(12):
                if ligne[j] == "0":
                    presence_0[j] += 1
    gamma = 0
    epsilon = 0
    for i in range(12):
        if presence_0[i] < 500:
            gamma += 2 ** (11 - i)
        else:
            epsilon += 2 ** (11 - i)
    print(gamma, epsilon)
    print(gamma * epsilon)


def j3b():
    liste = ["" for i in range(12)]
    with open("adventcalendar_3.txt") as fichier:
        for i in range(12):
            liste[i] = fichier.readline()
    oxygen = liste.copy()
    i = 0
    while len(oxygen) > 1:
        compte = 0
        for j in oxygen:
            if j[i] == "0":
                compte += 1
        print(compte)
        j = 0
        while j < len(oxygen):
            print(oxygen)
            print("ox:", oxygen[j])
            if oxygen[j][i] == "1" and compte > 6:
                print("out")
                oxygen.pop(j)
            elif oxygen[j][i] == "0" and compte == 6:
                print("out")
                oxygen.pop(j)
            elif oxygen[j][i] == "0" and compte < 6:
                print("out")
                oxygen.pop(j)
            else: j += 1
        i += 1
        i %= 5
    CO2 = liste.copy()
    i = 0
    while len(CO2) > 1:
        compte = 0
        for j in CO2:
            if j[i] == "0":
                compte += 1
        j = 0
        while j < len(CO2):
            if CO2[j][i] == "0" and compte > 6:
                CO2.pop(j)
            elif CO2[j][i] == "1" and compte == 6:
                CO2.pop(j)
            elif CO2[j][i] == "1" and compte < 6:
                CO2.pop(j)
            else: j += 1
        i += 1
        i %= 5
    ox = 0
    co = 0
    for k in range(5):
        if oxygen[0][k] == "1":
            ox += 2 ** (4-k)
        if CO2[0][k] == "1":
            co += 2 ** (4-k)
    print("oxygen", oxygen, ox)
    print("CO2", CO2, co)
    print(ox * co)


j3b()
# 2261546