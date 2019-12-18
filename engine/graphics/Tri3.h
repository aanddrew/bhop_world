#pragma once

#include "../math/Mat3.h"
#include "../math/Mat4.h"
#include <glm/glm.hpp>

namespace bh {

class Tri3 {
public:
    Tri3();
    Tri3(glm::vec3 a, glm::vec3 b, glm::vec3 c);
    Tri3(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 n);

    void apply_transform(glm::mat3 transform);
    void apply_transform(glm::mat4 transform);

    void split_by_plane(glm::vec3 plane_loc, glm::vec3 plane_dir, Tri3* returned) const;

    enum IN_FRONT_OF_PLANE {
        front,
        back,
        split
    };
    
    IN_FRONT_OF_PLANE in_front_of_plane(const glm::vec3& plane_loc, const glm::vec3& plane_dir) const;
    IN_FRONT_OF_PLANE center_in_front_of_plane(const glm::vec3& plane_loc, const glm::vec3& plane_dir) const;
    glm::vec3 get_normal() const;

    /*
    friend std::ostream& operator<<(std::ostream& os, const Tri3& tri){
        os << "Tri3:" << std::endl
           << "\ta: " << tri.a << std::endl
           << "\tb: " << tri.b << std::endl
           << "\tc: " << tri.c << std::endl
           << "\tn: " << tri.normal << std::endl;
        return os;
    }
    */

    bool isnan() const;

    float get_area() const;

    glm::vec3 a, b, c;
    glm::vec3 normal;
private:
};

}
