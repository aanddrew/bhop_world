#include "PhysTri3.h"

#include <iostream>

namespace bh {

PhysTri3::PhysTri3()
: Tri3()
{}

void print_vector(const glm::vec3& vec) {
    std::cout << "[" << vec.x << ", " << vec.y << ", " << vec.z << "]" << std::endl;
}

PhysTri3::PhysTri3(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 n) 
: Tri3(a, b, c, n)
{
    glm::vec3 center_of_triangle = (a + b + c)/3.0f;
    glm::vec3 norm_ab_hypothetical = glm::normalize(glm::cross((b-a), n));
    glm::vec3 norm_bc_hypothetical = glm::normalize(glm::cross((c-b), n));
    glm::vec3 norm_ac_hypothetical = glm::normalize(glm::cross((c-a), n));

    norm_ab = (glm::dot(norm_ab_hypothetical, (center_of_triangle - a)) > 0) 
            ? norm_ab_hypothetical 
            : norm_ab_hypothetical * -1.0f;
    norm_bc = (glm::dot(norm_bc_hypothetical, (center_of_triangle - b)) > 0) 
            ? norm_bc_hypothetical 
            : norm_bc_hypothetical * -1.0f;
    norm_ac = (glm::dot(norm_ac_hypothetical, (center_of_triangle - a)) > 0) 
            ? norm_ac_hypothetical 
            : norm_ac_hypothetical * -1.0f;

    static const float ONE_OVER_SQUARE_ROOT_TWO = 0.70711;
    i_am_a_floor = (glm::dot(normal, glm::vec3(0,1,0)) > ONE_OVER_SQUARE_ROOT_TWO);
}

PhysTri3::PhysTri3(const Tri3& triangle)
: PhysTri3(triangle.a, triangle.b, triangle.c, triangle.normal)
{}

bool PhysTri3::collide_player(Player& player, float dt) const {
    //glm::vec3 next_location = player.get_location() + (player.get_velocity() * dt);
    glm::vec3 next_location = player.get_location();
    glm::vec3 al = next_location - a;
    glm::vec3 bl = next_location - b;
    glm::vec3 cl = next_location - c;
    float dist_to_ab = glm::dot(norm_ab, al);
    float dist_to_bc = glm::dot(norm_bc, bl);
    float dist_to_ac = glm::dot(norm_ac, cl);
    float dist_to_plane = glm::dot(normal, al);
    if (dist_to_plane < player.get_radius() 
        && dist_to_plane > 0
        && dist_to_ab > 0
        && dist_to_bc > 0
        && dist_to_ac > 0) {
        /*
        std::cout << "colliding" << dist_to_plane << ", " 
            << dist_to_ab << ", " 
            << dist_to_bc<< ", " 
            << dist_to_ac << ", " 
            << std::endl;
        */
        //correct collision
        float dr = player.get_radius() - dist_to_plane;
        player.set_velocity(player.get_velocity() - normal * glm::dot(player.get_velocity(), normal));
        if (this->is_floor()) {
            player.set_airborne(false);
            //player.jump();
        }
        player.set_location(next_location + normal * dr);
        return true;
    }
    return false;
}

bool PhysTri3::is_floor() const {
    return i_am_a_floor;
}

}
