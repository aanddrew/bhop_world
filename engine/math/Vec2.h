#pragma once

#include <ostream>
#include <math.h>

namespace bh {

class Vec2 {
public:
    Vec2(float, float);
    Vec2();
    
    Vec2& operator =(const Vec2& other);

    Vec2  operator +(const Vec2& other) const;
    Vec2  operator -(const Vec2& other) const;
    Vec2  operator *(float scalar) const;
    Vec2  operator /(float scalar) const;

    float operator[](int index);

    float magnitude();
    float magnitude_squared();
    Vec2  normalize();

    static float dot(const Vec2& first, const Vec2& second);

    friend std::ostream& operator<<(std::ostream& os, const Vec2& vec){
        os << "<" << vec.x << ", " << vec.y << ">";
        return os;
    }

    float x, y;
};

}
