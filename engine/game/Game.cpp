#include "Game.h"

namespace bh {

GameSettings Game::settings = load_default_settings();

Game::Game(SDL_Window* window_in) 
: window(window_in),
  player(),
  pc(&player),
  map("maps/first_surf.obj", settings),
  shader("stage3/res/basicVertexShader.GLSL", 
    "stage3/res/basicFragmentShader.GLSL")
{
    paused = true;
    running = true;

    shader.bind();

    float nearZ = 0.01f;
    float farZ = 2000.0f;
    float ar = 16.0f/9.0f;
    float fov = 90.0f;

    shader.createUniform("perspective");
    shader.setUniform("perspective",  glm::perspective(fov, ar, nearZ, farZ));

    shader.createUniform("view");
    shader.setUniform("view", player.get_camera().getMatrix());

    shader.createUniform("model");
    shader.setUniform("model", glm::translate(glm::mat4(1.0), glm::vec3(1.0f, 0.0f, 0.0f)));
}

const GameSettings& Game::get_settings() {
    return settings;
}

bool Game::is_paused() const {
    return paused;
}

void Game::set_paused(bool paused_in) {
    paused = paused_in;
}

bool Game::is_running() const {
    return running;
}

void Game::update(float dt) {
    SDL_Event e;
    while(SDL_PollEvent(&e)) {
        if (e.type == SDL_KEYDOWN) {
            pc.KeyDown(e.key.keysym.sym);
            //pausing
            if (e.key.keysym.sym == SDLK_ESCAPE) {
                //window.setMouseCursorVisible(true);
                paused = true;
                return;
            }
            else if (e.key.keysym.sym == SDLK_b) {
                player.set_location(glm::vec3(0.0f, 0.0f, 0.0f));
            }
        }
        else if (e.type == SDL_KEYUP) {
            pc.KeyUp(e.key.keysym.sym);
            if (e.key.keysym.sym == SDLK_f) {
                pc.set_movement_mode((pc.get_movement_mode() == 
                                    bh::PlayerController::MODES::NOCLIP)
                                  ? bh::PlayerController::MODES::NORMAL
                                  : bh::PlayerController::MODES::NOCLIP);
                player.set_airborne(true);
            }
        }
        else if (e.type == SDL_MOUSEWHEEL) {
            if (player.jump()) {
                //jumpsound.play();
            }
        }
        else if (e.type == SDL_QUIT) {
            running = false;
        }

    }


	int x,y;
	SDL_GetMouseState(&x, &y);

    int w,h;
    SDL_GetWindowSize(window, &w, &h);
	// std::cout << "x: " << x << ", y: " << y << std::endl;
	int dx = x - (w/2);
	int dy = y - (h/2);

	pc.MouseInput(-1*dx, -1*dy);
    SDL_ShowCursor(0);

	if (dx != 0 || dy != 0)
		SDL_WarpMouseInWindow(window, w/2, h/2);

    //player.apply_gravity(glm::vec3(0.0f, -1 * settings.gravity, 0.0f), dt);
    if(pc.get_movement_mode() != bh::PlayerController::MODES::NOCLIP) {
        map.interact_player(player, dt);
    }
    pc.update(dt);
}

void Game::render() {
    shader.setUniform("view", player.get_camera().getMatrix());
    shader.bind();
    map.draw();
}

}
