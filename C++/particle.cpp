#include "particle.hpp"

namespace particle {
    Distance::Distance(Particle* part1, Particle part2) {
        vec::Vec2 l1 = part1->location;
        vec::Vec2 l2 = part2.location;
        dy = l2.y - l1.y;
        dx = l2.x - l1.x;
        dsq = dx * dx + dy * dy;
        dr = std::sqrt(dsq);
        if (dr == 0) {
            dr = 0.01;
        }
    }

    Distance::Distance(Particle part1, Particle part2) {
        vec::Vec2 l1 = part1.location;
        vec::Vec2 l2 = part2.location;
        dy = l2.y - l1.y;
        dx = l2.x - l1.x;
        dsq = dx * dx + dy * dy;
        dr = std::sqrt(dsq);
        if (dr == 0) {
            dr = 0.01;
        }
    }

    vec::Vec2 attraction(Particle* part1, Particle part2) {
        Distance dist(part1, part2);
        float f;

        if (dist.dr > 1) {
            f = (GRAVRATE * part1->mass * part2.mass) / dist.dsq;
            //std::cout << part1->mass << std::endl;
            return vec::Vec2(
                (f * dist.dx / dist.dr) / part1->mass,
                (f * dist.dy / dist.dr) / part1->mass
            );
        } else {
            f = 0;
            //std::cout << part1->mass << std::endl;

            return vec::Vec2(
                (f * dist.dx / dist.dr) / part1->mass,
                (f * dist.dy / dist.dr) / part1->mass
            );
        }
    }

    unsigned long _RGB(int r,int g, int b) {
		return b + (g<<8) + (r<<16);
	}
	
	void setColor(Display *dis, GC g, std::vector<int> rgb) {
		XSetForeground(dis, g, _RGB(rgb[0], rgb[1], rgb[2]));
	}

    Particle::Particle(vec::Vec2 velocity, vec::Vec2 location, float mass, std::vector<int> color){
        this->velocity = velocity;
        this->location = location;
        this->mass     = mass;
        this->color    = color;
    }

    void Particle::draw(Display *dis, Window win, GC gc) {
        setColor(dis, gc, color);
        std::vector<int> nl = location.normalize(width, height);
        XDrawArc(dis, win, gc, nl[0], nl[1], mass * 10, mass * 10, 0, 23040);
        XFillArc(dis, win, gc, nl[0], nl[1], mass * 10, mass * 10, 0, 23040);
        //XDrawPoint(dis, win, gc, nl[0], nl[1]);
    }

    void Particle::move() {
        location.addVec(velocity);
    }

    void Particle::merge(Particle part){
        if (mass < part.mass) {
            rem = true;
            float newvx = (part.velocity.x * part.mass + velocity.x * part.mass) / (part.mass + mass);
            float newvy = (part.velocity.y * part.mass + velocity.y * part.mass) / (part.mass + mass);
            part.velocity.addVec(vec::Vec2(newvx, newvy));
            part.mass += mass;
        } else {
            part.rem = true;
            float newvx = (velocity.x * mass + part.velocity.x * mass) / (mass + part.mass);
            float newvy = (velocity.y * mass + part.velocity.y * mass) / (mass + part.mass);
            velocity.addVec(vec::Vec2(newvx, newvy));
            mass += part.mass;
        }
    }

    void Particle::grav(std::vector<Particle> particles) {
        for (Particle &part : particles) {
            Particle* part1p = &part;
            Particle* part2p = this;
            if (part1p != part2p) {
                velocity.addVec(particle::attraction(this, part));
            }
        }
    }
}