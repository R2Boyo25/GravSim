#include "vec.hpp"

namespace vec {
    Vec2::Vec2(float x, float y) {
        this->x = x;
        this->y = y;
    }
    Vec2::Vec2(){}

    std::vector<int> Vec2::normalize(int width, int height){
        return {(int)round((width / 2) + x), (int)round((height / 2) + y)};
    }
    
    void Vec2::addVec(Vec2 vec) {
        x = x + vec.x;
        y = y + vec.y;
    }
}