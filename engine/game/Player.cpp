#include "Player.h"

#include <iostream>

namespace bh {

Player::Player() 
: Player({0.0f,0.0f,0.0f})
{}

Player::Player(const glm::vec3& start_location)
: velocity(0.0f, 0.0f, 0.0f)
{
    camera.setPos(start_location);
    airborne = false;
    move_speed = 13.0f;
}

void Player::update(float dt) {
    velocity += acceleration * dt;
    camera.translate(velocity * dt);
    //camera.movePos(glm::vec3(0.0f, 0.001f, 0.0f));
    std::cout << "camera:" << std::endl;
    std::cout << velocity.x << ", " << velocity.y << ", " << velocity.z << std::endl;
    std::cout << camera.getPos().x << ", " << camera.getPos().y << ", " << camera.getPos().z << std::endl;
}

void Player::accelerate(const glm::vec3& wishdir, float dt) {
    if (airborne) {
        air_accelerate(wishdir, dt);
    }
    else {
        ground_accelerate(wishdir, dt);
    }
        
    //std::cout << glm::length(velocity) << std::endl;
}

void Player::set_velocity(const glm::vec3& wishvel) {
    velocity = wishvel;
}
void Player::set_location(const glm::vec3& wishloc) {
    camera.setPos(wishloc);
}

s3::Camera& Player::get_camera() {
    return camera;
}

const glm::vec3& Player::get_location() const {
    return camera.getPos();
}

const glm::vec3& Player::get_velocity() const {
    return velocity;
}

float Player::get_radius() const {
    return 2.0f;
}

bool Player::is_airborne() const {
    return airborne;
}

void Player::set_airborne(bool new_air) {
    airborne = new_air;
}

bool Player::is_walking() const {
    return walking;
}

void Player::set_walking(bool new_walk) {
    walking = new_walk;
}

bool Player::jump() {
    if(!airborne) {
        set_airborne(true);
        velocity += glm::vec3(0.0f, 15.0f, 0.0f);
        return true;
    }
    return false;
}

float Player::get_move_speed() const {
    return move_speed;
}

void Player::set_move_speed(float new_speed) {
    move_speed = new_speed;
}

void Player::ground_accelerate(const glm::vec3& wishdir, float dt) {
    float speed_now = move_speed;
    if (walking)
        speed_now *= 0.5;

    velocity += wishdir * speed_now * 10.0f * dt;
    float mag_velocity = glm::length(glm::vec3(velocity.x, 0, velocity.z));
    if (mag_velocity > speed_now) {
        float multi = speed_now/mag_velocity;
        velocity.x *= multi;
        velocity.z *= multi;
    }
    //apply ground friction
    float friction = speed_now * 0.5f * dt;
    velocity = velocity - (velocity * friction);
}

//code literally copied directly from source sdk
void Player::air_accelerate(const glm::vec3& wishdir, float dt) {
    float accel = 1500;
    float currentspeed = glm::length(glm::vec3(velocity.x, 0, velocity.z));
    float addspeed = 0.1;
    float accelspeed = 0.1;
	float wishspd = 1;

    float air_speed_cap = 70.0f;

	// Cap speed
	if ( wishspd > air_speed_cap )
		wishspd = air_speed_cap;

	// Determine veer amount
    currentspeed = glm::dot(velocity, wishdir);

	// See how much to add
	addspeed = wishspd - currentspeed;

	// If not adding any, done.
	if (addspeed <= 0)
		return;

	// Determine acceleration speed after acceleration
	accelspeed = accel * wishspd * dt;

	// Cap it
	if (accelspeed > addspeed)
		accelspeed = addspeed;
	
	// Adjust pmove vel.
    velocity = velocity + (wishdir * accelspeed);
}

void Player::bleed_speed(float fraction) {
    //float currentspeed = glm::vec3(velocity.x, 0, velocity.z).magnitude();
    //newspeed *= (1 - fraction);
    velocity.x *= (1 - fraction);
    velocity.z *= (1 - fraction);
}
    
}

