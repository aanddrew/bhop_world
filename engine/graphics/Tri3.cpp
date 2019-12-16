#include "Tri3.h"

#include <iostream>

namespace bh {

Tri3::Tri3() {}

Tri3::Tri3(glm::vec3 a, glm::vec3 b, glm::vec3 c) {
    this->a = a;
    this->b = b;
    this->c = c;

    glm::vec3 ab = b - a;
    glm::vec3 ac = c - a;
    this->normal = glm::normalize(glm::cross(ab, ac));
}

Tri3::Tri3(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 n) {
    this->a = a;
    this->b = b;
    this->c = c;
    this->normal = n;
}

void Tri3::apply_transform(glm::mat3 transform) {
    a = a * transform;
    b = b * transform;
    c = c * transform;
}

void Tri3::apply_transform(glm::mat4 transform) {
    a = glm::vec4(a, 1.0f) * transform;
    b = glm::vec4(b, 1.0f) * transform;
    c = glm::vec4(c, 1.0f) * transform;
}

//splits a triangle along a plane, fills the returned array with the 
//3 resulting triangles.
//assumes that the plane actually intersects the triangle.
void Tri3::split_by_plane(glm::vec3 plane_loc, glm::vec3 plane_dir, Tri3* returned) const {
    //get the plane in the form of ax + by + cz = d
    float plane_a = plane_dir[0];
    float plane_b = plane_dir[1];
    float plane_c = plane_dir[2];
    float plane_d = glm::dot(plane_loc, plane_dir);

    //t1, t2, t3 are how far the plane intersects between:
    //ab, bc, ac respectively
    
    glm::vec3 ab = b - a;
    glm::vec3 bc = c - b;
    glm::vec3 ac = c - a;
    
    //ab
    float t1 = 
        (plane_d 
        - plane_a*this->a[0] 
        - plane_b*this->a[1] 
        - plane_c*this->a[2]
        )
        /
        (plane_a*ab[0] + plane_b*ab[1] + plane_c*ab[2]);
    glm::vec3 intersect_d = this->a + ab*t1;

    float t2 = 
        (plane_d 
        - plane_a*this->b[0] 
        - plane_b*this->b[1] 
        - plane_c*this->b[2]
        )
        /
        (plane_a*bc[0] + plane_b*bc[1] + plane_c*bc[2]);
    glm::vec3 intersect_e = this->b + bc*t2;

    float t3 = 
        (plane_d 
        - plane_a*this->a[0] 
        - plane_b*this->a[1] 
        - plane_c*this->a[2]
        )
        /
        (plane_a*ac[0] + plane_b*ac[1] + plane_c*ac[2]);
    glm::vec3 intersect_f = this->a + ac*t3;

    //d is not in triangle
    if (t1 < 0 || t1 > 1) {
        Tri3 tri_1(this->c, intersect_e, intersect_f);
        Tri3 tri_2(this->a, intersect_e, intersect_f);
        Tri3 tri_3(this->b, this->a, intersect_e);
        returned[0] = tri_1;
        returned[1] = tri_2;
        returned[2] = tri_3;
    }
    //e is not in triangle
    else if (t2 < 0 || t2 > 1) {
        Tri3 tri_1(this->a, intersect_d, intersect_f);
        Tri3 tri_2(this->b, intersect_d, intersect_f);
        Tri3 tri_3(this->c, this->b, intersect_f);
        returned[0] = tri_1;
        returned[1] = tri_2;
        returned[2] = tri_3;
    }
    //f is not in triangle
    else {
        Tri3 tri_1(this->b, intersect_d, intersect_e);
        Tri3 tri_2(this->c, intersect_d, intersect_e);
        Tri3 tri_3(this->a, this->c, intersect_d);
        returned[0] = tri_1;
        returned[1] = tri_2;
        returned[2] = tri_3;
    }
}

Tri3::IN_FRONT_OF_PLANE Tri3::in_front_of_plane(const glm::vec3& plane_loc, const glm::vec3& plane_dir) const {
    glm::vec3 la = a - plane_loc;
    glm::vec3 lb = b - plane_loc;
    glm::vec3 lc = c - plane_loc;
    
    float dot_a = glm::dot(plane_dir, la);
    float dot_b = glm::dot(plane_dir, lb);
    float dot_c = glm::dot(plane_dir, lc);
    
    if (dot_a >= -0.01 && dot_b >= -0.01 && dot_c >= -0.01) {
        return IN_FRONT_OF_PLANE::front;
    }
    else if (dot_a <= 0.01 && dot_b <= 0.01 && dot_c <= 0.01) {
        return IN_FRONT_OF_PLANE::back;
    }
    else {
        return IN_FRONT_OF_PLANE::split;
    }
}

Tri3::IN_FRONT_OF_PLANE Tri3::center_in_front_of_plane(const glm::vec3& plane_loc, const glm::vec3& plane_dir) const {
    glm::vec3 center = (a + b + c) /3.0f;
    glm::vec3 loc_center = center - plane_loc;
    if (glm::dot(loc_center, plane_dir) > 0){
        return IN_FRONT_OF_PLANE::front;
    }
    else {
        return IN_FRONT_OF_PLANE::back;
    }
}

glm::vec3 Tri3::get_normal() const {
    return normal;
}

bool Tri3::isnan() const {
    for(int i = 0; i < 3; i ++) {
        if (std::isnan(a[i]) || std::isnan(b[i]) || std::isnan(c[i]) || std::isnan(normal[i]))
            return true;
    }
    return false;
}

float Tri3::get_area() const {
    glm::vec3 ab = b - a;
    glm::vec3 ac = c - a;
    float parallelogram_area = glm::length(glm::cross(ab, ac));
    return parallelogram_area/2;
}

}
