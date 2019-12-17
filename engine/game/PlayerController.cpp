#include "PlayerController.h"

#include <iostream>

#include "Game.h"
#include "GameSettings.h"

namespace bh {
    
PlayerController::PlayerController(Player* player_in) 
: player(player_in)
{
    for(int i = 0; i < NUM_MOVE_FLAGS; i++) {
        moving[i] = false;
    }
    movement_mode = NOCLIP;
    noclip_speed = 50.0f;
}

void PlayerController::KeyDown(SDL_Keycode key) {
    if (key == Game::get_settings().forward_key){
        moving[FORWARD] = true;
    }
    else if (key == Game::get_settings().backward_key) {
        moving[BACKWARD] = true;
    }
    else if (key == Game::get_settings().left_key) {
        moving[LEFT] = true;
    }
    else if(key == Game::get_settings().right_key) {
        moving[RIGHT] = true;
    }
    else if (key == Game::get_settings().jump_key) {
        moving[JUMP] = true;
    }
    else if (key == Game::get_settings().walk_key) {
        moving[WALK] = true;
        player->set_walking(true);
        player->bleed_speed(0.2);
    }
}

void PlayerController::KeyUp(SDL_Keycode key) {
    if (key == Game::get_settings().forward_key){
        moving[FORWARD] = false;
    }
    else if (key == Game::get_settings().backward_key) {
        moving[BACKWARD] = false;
    }
    else if (key == Game::get_settings().left_key) {
        moving[LEFT] = false;
    }
    else if(key == Game::get_settings().right_key) {
        moving[RIGHT] = false;
    }
    else if(key == Game::get_settings().jump_key) {
        moving[JUMP] = false;
    }
    else if (key == Game::get_settings().walk_key) {
        moving[WALK] = false;
        player->set_walking(false);
    }
}

void PlayerController::MouseInput(float dx, float dy) {
    glm::vec3 xz_forward =
        glm::normalize(
            glm::vec3(
                player->get_camera().getForward().x, 
                0.0f, 
                player->get_camera().getForward().z
            )
        );
    
    float yaw = glm::dot(player->get_camera().getForward(), xz_forward);
    bool allow_yaw = true;
    //yaw never becomes negative
    if (yaw < 0.01) {
        if (player->get_camera().getForward().y > 0) {
            if (dy > 0)
                allow_yaw = false;
        }
        else {
            if (dy < 0)
                allow_yaw = false;
        }
    }

    if (allow_yaw)
        player->get_camera().rotateUp(dy * 0.005);
    player->get_camera().rotateRight(dx * 0.005);
}

void PlayerController::update(float dt) {
    switch(movement_mode) {
        case NOCLIP: {
            glm::vec3 wishdir(0.0f,0.0f,0.0f);
            if (moving[RIGHT]){
                wishdir += player->get_camera().getRight();
            }
            if (moving[LEFT]){
                wishdir -= player->get_camera().getRight();
            }
            if (moving[FORWARD]){
                wishdir += player->get_camera().getForward();
            }
            if (moving[BACKWARD]){
                wishdir -= player->get_camera().getForward();
            }

            //now normalize it to the x/z plane
            //player->accelerate(wishdir, dt);
            player->set_velocity(wishdir * noclip_speed);
            player->update(dt);
        }
        break;
        case NORMAL: {
            glm::vec3 wishdir(0.0f, 0.0f, 0.0f);
            if (moving[RIGHT]){
                wishdir += player->get_camera().getRight();
            }
            if (moving[LEFT]){
                wishdir -= player->get_camera().getRight();
            }
            if (moving[FORWARD]){
                wishdir += player->get_camera().getForward();
            }
            if (moving[BACKWARD]){
                wishdir -= player->get_camera().getForward();
            }

            if (moving[JUMP] && !player->is_airborne()) {
                player->jump();
            }
    
            glm::vec3 wishdir_xz(wishdir.x, 0.0f, wishdir.z);
            //now normalize it to the x/z plane
            if (glm::length(wishdir_xz) != 0) 
                wishdir_xz = glm::normalize(wishdir_xz);
            player->accelerate(wishdir_xz, dt);
            player->update(dt);

        }
        break;
    }
}

PlayerController::MODES PlayerController::get_movement_mode() const {
    return movement_mode;
}

void PlayerController::set_movement_mode(MODES mode) {
    movement_mode = mode;
}

}
