from dataclass import Velocity, Location, Distance
from particle import Particle
import random
import pygame

MERGE_THRESHOLD = 5

screen = pygame.display.set_mode([500, 500])

width  = pygame.display.Info().current_w / 2
height = pygame.display.Info().current_h / 2

def start():
    global particles
    particles = [
        Particle(
            velocity = Velocity(), 
            location = Location(
                    random.randint(-width, width), 
                    random.randint(-height, height)
                ), 
            mass = 0.5,
            color = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))
        ) for i in range(0, 250)]

def rem():
    newParticles = []
    for part in particles:
        if not part.rem:
            newParticles.append(part)
    return newParticles

def merge():
    for part1 in particles:
        for part2 in particles:
            if part1 is not part2 and not (part2.rem or part1.rem):
                if Distance(part1, part2).dr < MERGE_THRESHOLD * ((part1.mass * part2.mass)):
                    part1.Merge(part2)

start()

running = True
#frame = 0
f = True
while running:
    particles = rem()
    merge()

    if len(particles) == 0:
        start()

    pygame.display.set_caption(str(len(particles)))

    if f: screen.fill((0,0,0))

    # Did the user click the window close button?
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.KEYDOWN:
            f = not f

    for particle in particles:
        particle.grav(particles)
        particle.move()
        particle.draw(screen)
        #print(particle.location)
    
    #frame += 1
    #print(frame)

    pygame.display.flip()

pygame.quit()