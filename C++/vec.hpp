#pragma once
#include <vector>
#include <cmath>

namespace vec {
    class Vec2{
        public:
            float x = 0;
            float y = 0;

            Vec2(float x, float y);
            Vec2();

            std::vector<int> normalize(int width = 100, int height = 100);
            void addVec(Vec2 vec);
    };    
}