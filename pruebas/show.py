
class Tamagotchi:
    def __init__(self, name):
        self.name = name
        self.hunger = 0
        self.tiredness = 0
        

with open("sprites.txt", "r") as file:
    a = 0
    count = 0
    for line in file.readlines():
        if len(line) > a:
            a = len(line)
        print(line[:-2])
        count += 1
    print(a, count % 42)
        
a = Tamagotchi("Rigoberto")
b = "Token funciona"
