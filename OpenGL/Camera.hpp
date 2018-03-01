#ifndef CAMERA_HPP
#define CAMERA_HPP
#include <iostream>
#include "glm\glm.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
private:

public:
	glm::fvec3 pos;
	glm::fvec3 rot;

	Camera(glm::fvec3 _pos, glm::fvec3 _rot);
	~Camera();
	void MoveForeward(float distance);
	void MoveBackward(float distance);
	void MoveLeft(float distance);
	void MoveRight(float distance);
	void MovePosition(glm::fvec3 _offPos);
	void Rotate(float horizontal, double vertical);
	glm::fmat4 GetViewMatrix();
};



#endif