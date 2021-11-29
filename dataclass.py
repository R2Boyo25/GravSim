import math

class Vec2:
    def __init__(self, x = 0, y = 0):
        self.x = x
        self.y = y

    def normalize(self, width = 100, height = 100):
        return (width/2)+(self.x), (height/2)-(self.y)
    
    def addVec(self, vec):
        #print(self, "+", vec)
        self.x = self.x + vec.x 
        self.y = self.y + vec.y

    def __str__(self):
        return f"({self.x}, {self.y})"

class Location(Vec2):
    pass

class Velocity(Vec2):
    pass

class Distance:
    def __init__(self, part1, part2):
        part1 = part1.location
        part2 = part2.location
        self.dy = part2.y - part1.y
        self.dx = part2.x - part1.x
        self.dsq = self.dx * self.dx + self.dy * self.dy
        self.dr = math.sqrt(self.dsq)
        if self.dr == 0:
            self.dr = 0.01

class Center:
    def __init__(self):
        self.location = Location(0, 0)
        self.mass = 50