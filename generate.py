import random

for x_file in range(16):
    file_name = "gambler" + str(x_file) + ".txt"
    gambler_file = open(file_name, "w")
    for x_count in range(10):
        gambler_file.write(str(random.randrange(-1000,1000)) + "\n")
