#pragma once

#include "../graphics/Tri3.h"
#include "../game/Player.h"

namespace bh {

class PhysTri3 : public Tri3 {
public:
    PhysTri3();
    PhysTri3(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec3 n);
    PhysTri3(const Tri3& triangle);

    //bool is_sphere_colliding(const glm::vec3& location, float radius) const;
    bool collide_player(Player& player, float dt) const;
    bool is_floor() const;
private:
    glm::vec3 norm_ab, norm_bc, norm_ac;
    bool i_am_a_floor;
};
    
}
