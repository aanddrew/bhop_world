#include "Camera.h"

#include <iostream>

#include <glm/gtc/quaternion.hpp>
namespace s3
{

Camera::Camera()
:
pos(0.0f, 0.0f, 0.0f)
{
	//pos = glm::vec3(0.0f, 0.0f, 0.0f);
	//construct our frame
	forward = glm::vec3(0.0f, 0.0f, -1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	right = glm::cross(forward, up);
	// std::cout << "right vector: [" << right[0] << ", " << right[1] << ", " << right[2] << "]" << std::endl;
}

glm::mat4 Camera::getMatrix() const
{
	return glm::lookAt(pos, pos + forward, up);
}

//pitch, done via local coordinates
//the angle is in radians
void Camera::rotateUp(float dTheta)
{	
	//rotation using quaternions
	glm::quat rotation = glm::angleAxis(dTheta, right);
	glm::mat4 rotationMatrix = glm::mat4_cast(rotation);

	forward = rotationMatrix*(glm::vec4(forward, 1.0));
	up = rotationMatrix*(glm::vec4(up, 1.0));

	// up = glm::cross(right, forward);
	normalizeFrame();
}

//yaw - done via global coordinates
//the angle is in radians
void Camera::rotateRight(float dTheta)
{
	//rotation using quaternions
	glm::quat rotation = glm::angleAxis(dTheta, glm::vec3(0, 1, 0));
	glm::mat4 rotationMatrix = glm::mat4_cast(rotation);

	//rotate all our vectors according to the rotation matrix
	forward = rotationMatrix*(glm::vec4(forward, 1.0));
	right = rotationMatrix*(glm::vec4(right, 1.0));
	up = rotationMatrix*(glm::vec4(up, 1.0));

	// right = glm::cross(forward, up);
	normalizeFrame();
}

void Camera::translate(const glm::vec3& translation)
{
	pos = pos + translation;
}

void Camera::setPos(glm::vec3 newPos)
{
	pos = newPos;
}

void Camera::normalizeFrame()
{
	forward = normalize(forward);
	up = normalize(up);
	right = normalize(right);
}

const glm::vec3& Camera::getForward() const {return forward;}
const glm::vec3& Camera::getRight() const {return right;}
const glm::vec3& Camera::getUp() const {return up;}
const glm::vec3& Camera::getPos() const {return pos;}

}
