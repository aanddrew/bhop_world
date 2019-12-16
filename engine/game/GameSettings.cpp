#include "GameSettings.h"

#include <iostream>
#include <fstream>

namespace bh {

void load_settings_from_file(const std::string& file_name, GameSettings& settings) {
    std::ifstream cfg_file(file_name);
    std::string line;
    while(std::getline(cfg_file, line)) {
        std::cout << line << std::endl;
    }
}

GameSettings load_default_settings() {
    return {
        0.01,
        0.01,
        0.01,
        25,
        SDLK_w,
        SDLK_s,
        SDLK_d,
        SDLK_a,
        SDLK_SPACE,
        SDLK_LSHIFT,
    };
}

}
