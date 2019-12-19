#pragma once

#include <stage3/stage3.h>
#include <vector>
#include <string>
#include "../physics/PhysTri3.h"
#include "GameSettings.h"
#include "Bsp.h"

namespace bh {
 
class Map {
public:
    Map(const std::string& file_name, const GameSettings& settings);

    void draw();
    void interact_player(Player& player, float dt) const;
private:
    void collide_player(Player& player, float dt) const;
    void apply_gravity_player(Player& player, float dt) const;

    std::vector<PhysTri3> phys_triangles;
    Bsp bsp;
    s3::Mesh mesh;
    s3::Texture texture;

    const GameSettings * settings;
};

}
