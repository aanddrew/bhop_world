#pragma once

#include <stage3/graphics/Camera.h>

namespace bh {
    
//A player is a camera that moves.
class Player {
public:
    Player();
    Player(const glm::vec3& start_location);

    s3::Camera& get_camera();

    void update(float dt);

    const glm::vec3& get_location() const;
    const glm::vec3& get_velocity() const;

    void accelerate(const glm::vec3& wishdir, float dt);
    void set_velocity(const glm::vec3& wishvel);
    void set_location(const glm::vec3& wishloc);
    void apply_gravity(const glm::vec3& gravity, float dt);

    void bleed_speed(float fraction);

    bool is_airborne() const;
    void set_airborne(bool new_air);

    bool is_walking() const;
    void set_walking(bool new_walk);

    float get_move_speed() const;
    void set_move_speed(float new_speed);

    bool jump();

    float get_radius() const;
private:
    s3::Camera camera;
    glm::vec3 velocity;
    glm::vec3 acceleration;

    void ground_accelerate(const glm::vec3& wishdir, float dt);
    void air_accelerate(const glm::vec3& wishdir, float dt);

    float move_speed;

    bool airborne;
    bool walking;
};

}
