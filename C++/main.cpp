#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <stdlib.h>
#include "particle.hpp"
#include "vec.hpp"
#include <experimental/random>
#include <iostream>

using namespace std;
using namespace particle;
using namespace vec;

float GRAVRATE        = 0.5;
int   STARTAMOUNT     = 100;
int   MERGE_THRESHOLD = 2;
bool  REDRAW          = true;
Particle CENTER(Vec2(), Vec2(), 100, {1, 1, 1});

Display *dis;
int screen;
Window win;
GC gc;

int width = 500;
int height = 500;

vector<Particle> particles = {};

void init_x();
void close_x();
void redraw();
vector<int> windowDimensions();

void start() {
    for (int i = 0; i <= STARTAMOUNT; i++) {
        particles.push_back(Particle(
            Vec2(0, 0),
            Vec2(
                std::experimental::randint(-(width/2), width/2),
                std::experimental::randint(-(height/2), height/2)
            ),
            0.5, 
            {
                std::experimental::randint(0, 255),
                std::experimental::randint(0, 255),
                std::experimental::randint(0, 255)
            }
        ));
    }
}

typeof particles rem() {
    typeof particles new_particles = {};
    for (auto &part : particles) {
        if (!part.rem) {
            new_particles.push_back(part);
        }
    }

    return new_particles;
}

void merge() {
    for(auto& part1 : particles) {
        for(auto& part2 : particles) {
            Particle* part1p = &part1;
            Particle* part2p = &part2;
            if (part1p != part2p) {
                if (Distance(part1p, part2).dr < MERGE_THRESHOLD * (part1.mass * part2.mass)) {
                    part1.merge(part2);
                }
            }
        }
    }
}

int main (int argc, char* argv[]) {
	init_x();
    start();

	while(1) {	

        width = windowDimensions()[0];	
        height = windowDimensions()[1];

        particles = rem();
        merge();

        if (REDRAW){
            redraw();
        }

        for (auto& particle : particles) {
            particle.grav(particles);
            particle.grav({CENTER});
            particle.move();
            particle.draw(dis, win, gc);
            //std::cout << particle.location.x << " " << particle.location.y << endl;
        }

		XFlush(dis);
	}
}


vector<int> windowDimensions() {
    XWindowAttributes window_attributes_return;
    XGetWindowAttributes(dis, win, &window_attributes_return);

    int width = window_attributes_return.width;
    int height = window_attributes_return.height;

    return {width, height};
}

void init_x() {       
	unsigned long black,white;

	dis=XOpenDisplay((char *)0);
   	screen=DefaultScreen(dis);
	black=BlackPixel(dis,screen),
	white=WhitePixel(dis, screen);
   	win=XCreateSimpleWindow(dis,DefaultRootWindow(dis),0,0,	
		width, height, 5, white, black);
	XSetStandardProperties(dis,win,"Gravity Sim","Gravity Sim",None,NULL,0,NULL);
	XSelectInput(dis, win, ExposureMask|ButtonPressMask|KeyPressMask);
        gc=XCreateGC(dis, win, 0,0);        
	XSetBackground(dis,gc,black);
	XSetForeground(dis,gc,white);
	XClearWindow(dis, win);
	XMapRaised(dis, win);
};

void close_x() {
	XFreeGC(dis, gc);
	XDestroyWindow(dis,win);
	XCloseDisplay(dis);	
	std::exit(1);				
};

void redraw() {
	XClearWindow(dis, win);
};