
class Tamagotchi:
    def __init__(self, name):
        self.name = name
        self.hunger = 0
        self.tiredness = 0
        

with open("doraemon_pistola.txt", "r") as file:
    for line in file.readlines():
        print(line)
        
a = Tamagotchi("Rigoberto")
