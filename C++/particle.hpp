#include "vec.hpp"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <vector>

#include<iostream>

#pragma once

extern int width;
extern int height;
extern float GRAVRATE;

namespace particle {
    class Particle {
        public:
            vec::Vec2        location;
            vec::Vec2        velocity;
            float           mass;
            std::vector<int> color;
            bool             rem = false;

            Particle(vec::Vec2 velocity = vec::Vec2(1, 5), vec::Vec2 location = vec::Vec2(0, 0), float mass = 1, std::vector<int> color = {255, 255, 255});
            void draw(Display *dis, Window win, GC gc);
            void move();
            void merge(Particle part);
            void grav(std::vector<Particle> particles);
    };

    vec::Vec2 attraction(Particle* part1, Particle part2);

    class Distance{
        public:
            float dy;
            float dx;
            float dsq;
            float dr;

            Distance(Particle* part1, Particle part2);
            Distance(Particle part1, Particle part2);
    };
}