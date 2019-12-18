#include "Map.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace bh {

//to help with parsing file, thanks CSCI 1300
void split(const std::string& temp, std::string filled[], char del, int max_words) {
    std::stringstream temp_stream(temp);
    int i = 0; 
    std::string sub_temp;
    while(std::getline(temp_stream, sub_temp, del)) {
        if (i == max_words)
            return;
        filled[i] = sub_temp;
        i++;
    }
}
    
Map::Map(const std::string& file_name, const GameSettings& settings) 
: mesh(file_name),
  texture("res/cobble.png")
{
    this->settings = &settings;
    //read in an obj file, and populate the array of triangles
    std::ifstream in_file(file_name);
    texture.load();
    mesh.load();


    if(!in_file.is_open()) {
        std::string err_message = "ERROR: CANNOT OPEN MESH FILE: " + file_name + ".";
        throw std::invalid_argument(err_message);
        return;
    }
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec3> temp_normals;
    std::vector<int> temp_vertex_indeces;
    std::vector<int> temp_normal_indeces;
    std::string line;
    while(std::getline(in_file, line)) {
        if (line[0] == '#')
            continue;
        else if (line[0] == 'v') {
            if (line[1] == 'n') {
                std::string filled[4];
                split(line, filled, ' ', 4);
                temp_normals.push_back(
                    glm::vec3(
                        std::stof(filled[1]),
                        std::stof(filled[2]),
                        std::stof(filled[3])
                    )
                );

            }
            else if (line[1] == ' ') {
                std::string filled[4];
                split(line, filled, ' ', 4);
                temp_vertices.push_back(
                    glm::vec3(
                        std::stof(filled[1]),
                        std::stof(filled[2]),
                        std::stof(filled[3])
                    )
                );
            }
        }
        else if (line[0] == 'f') {
            std::string filled[4];
            split(line, filled, ' ', 4);
            for(int i = 1; i < 4; i++) {
                std::string filled_mini[3];
                split(filled[i], filled_mini, '/', 3);
                std::string vertex_string = filled_mini[0];
                std::string normal_string = filled_mini[2];
                temp_vertex_indeces.push_back(std::stoi(vertex_string) - 1);
                temp_normal_indeces.push_back(std::stoi(normal_string) - 1);
            }
        }
    }

    for(size_t i = 0; i < temp_vertex_indeces.size(); i+=3) {
        phys_triangles.push_back(
            PhysTri3(
                temp_vertices.at(temp_vertex_indeces.at(i)),
                temp_vertices.at(temp_vertex_indeces.at(i+1)),
                temp_vertices.at(temp_vertex_indeces.at(i+2)),
                temp_normals.at(temp_normal_indeces.at(i + 1))
            )
        );
    }
}

void Map::collide_player(Player& player, float dt) const {
    for (size_t i = 0; i < phys_triangles.size(); i++) {
        phys_triangles.at(i).collide_player(player, dt);
    }
    /*
    for(auto& triangle : phys_triangles) {
        triangle.collide_player(player, dt);
    }
    */
}

void Map::interact_player(Player& player, float dt) const {
    apply_gravity_player(player, dt);
    collide_player(player, dt);
}

void Map::apply_gravity_player(Player& player, float dt) const {
    player.set_velocity(player.get_velocity() + glm::vec3(0, -1*settings->gravity, 0) * dt);
}

void Map::draw() {
    texture.bind();
    mesh.bind();
    mesh.draw();
}

}
