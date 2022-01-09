from dataclass import Velocity, Location, Distance, Center
import pygame
import math

GRAVRATE = 1.3
CENTER = Center()

def attraction(par1, par2) -> Velocity:
    '''GMm/R**2'''
    dist = Distance(par1, par2)
    f = (GRAVRATE * par1.mass * par2.mass) / dist.dsq if dist.dr > 1 else 0
    return Velocity(
        (f * dist.dx / dist.dr) / par1.mass,
        (f * dist.dy / dist.dr) / par1.mass
    )

class Particle:
    def __init__(self, 
                velocity = Velocity(1, 5), 
                location = Location(0, 0), 
                mass = 1, 
                color = (255, 255, 255)
            ):
        self.velocity = velocity
        self.location = location
        self.mass = mass
        self.color = color
        self.rem = False
    
    def draw(self, screen):
        width  = pygame.display.Info().current_w
        height = pygame.display.Info().current_h
        #if abs(self.location.normalize(width, height)[0]) > width or abs(self.location.normalize(width, height)[1]) > height:
        #    self.rem = True
        pygame.draw.circle(screen, self.color, self.location.normalize(width, height), self.mass * 2)
    
    def move(self):
        self.location.addVec(self.velocity)
    
    def Merge(self, part):
        # https://www.thanassis.space/gravity.html
        if self.mass < part.mass:
            p1, p2 = part, self
        else:
            p1, p2 = self, part

        p2.rem = True
        newvx = (p1.velocity.x*p1.mass+p2.velocity.x*p2.mass)/(p1.mass+p2.mass)
        newvy = (p1.velocity.y*p1.mass+p2.velocity.y*p2.mass)/(p1.mass+p2.mass)
        p1.velocity.addVec(Velocity(newvx, newvy))
        p1.mass += p2.mass

    def grav(self, particles):
        width  = pygame.display.Info().current_w
        height = pygame.display.Info().current_h
        for part in particles:
            if part is not self:
                self.velocity.addVec(attraction(self, part))
        '''
        if abs(self.location.normalize(width, height)[0]) > width or abs(self.location.normalize(width, height)[1]) > height:
            a = attraction(self, CENTER)
            dist = Distance(self, CENTER)
            self.velocity.addVec(Velocity(a.x * dist.dx, a.y * dist.dy))
        else:
            self.velocity.addVec(attraction(self, CENTER))
        '''