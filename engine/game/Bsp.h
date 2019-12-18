#pragma once

#include <memory>
#include <vector>
#include "../physics/PhysTri3.h"

namespace bh {

struct node {
    PhysTri3 triangle;
    std::unique_ptr<node> front;
    std::unique_ptr<node> back;
};

class Bsp {
public:
    Bsp();
    Bsp(const std::vector<PhysTri3>& triangles);
    //void draw_bsp(const Camera& camera, sf::RenderWindow& window) const;
private:
    std::unique_ptr<node> build_bsp(const std::vector<PhysTri3>& triangles);
    std::unique_ptr<node> head;
};

}
