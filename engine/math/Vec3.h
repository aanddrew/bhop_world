#pragma once

#include <ostream>
#include <math.h>

namespace bh {

class Vec3 {
public:
    Vec3(float, float, float);
    Vec3();
    
    Vec3& operator =(const Vec3& other);

    Vec3  operator +(const Vec3& other) const;
    Vec3  operator -(const Vec3& other) const;
    Vec3  operator *(float scalar) const;
    Vec3  operator /(float scalar) const;
    
    float operator[](int index);

    float magnitude();
    float magnitude_squared();
    Vec3  normalize();

    static float  dot(const Vec3& first, const Vec3& second);
    static Vec3 cross(const Vec3& first, const Vec3& second);

    friend std::ostream& operator<<(std::ostream& os, const Vec3& vec){
        os << "<" << vec.x << ", " << vec.y << ", " << vec.z << ">";
        return os;
    }

    float x, y, z;
};

}
