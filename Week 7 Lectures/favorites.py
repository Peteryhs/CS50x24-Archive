import csv

with open("favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    scratch, python, c = 0, 0, 0
    counts = {}

    for row in reader:
        favorite = row["problem"]
        if favorite in counts:
            counts[favorite] += 1
        else:
            counts[favorite] = 1

fav = input()
print(f"{fav}:{counts[fav]}")
