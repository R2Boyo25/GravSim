from math import sqrt

class Vec2:
    __slots__ = ("x", "y")
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
    __slots__ = ("dy", "dx", "dsq", "dr")
    def __init__(self, part1, part2):
        part1 = part1.location
        part2 = part2.location
        self.dy = part2.y - part1.y
        self.dx = part2.x - part1.x
        self.dsq = self.dx * self.dx + self.dy * self.dy
        self.dr = sqrt(self.dsq) or 0.01 # square root of distance^2 or 0.01 if it is 0 (prevents 0 division errors in attraction)

class Center:
    __slots__ = ("location", "mass")
    def __init__(self):
        self.location = Location(0, 0)
        self.mass = 25