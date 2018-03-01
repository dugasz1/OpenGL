#include "Camera.hpp"

Camera::Camera(glm::fvec3 _pos, glm::fvec3 _rot)
{
	this->pos = _pos;
	this->rot = _rot;
}

Camera::~Camera()
{
}

void Camera::MoveForeward(float distance) {
	double angle = glm::radians(this->rot.y);

	this->pos.z += cos(angle) * distance;
	this->pos.x -= sin(angle) * distance;
}

void Camera::MoveBackward(float distance) {
	double angle = glm::radians(this->rot.y);

	this->pos.z -= cos(angle) * distance;
	this->pos.x += sin(angle) * distance;
}

void Camera::MoveLeft(float distance) {
	double angle = glm::radians(this->rot.y + 90.0);

	this->pos.z -= cos(angle) * distance;
	this->pos.x += sin(angle) * distance;
}

void Camera::MoveRight(float distance) {
	double angle = glm::radians(this->rot.y - 90.0);

	this->pos.z -= cos(angle) * distance;
	this->pos.x += sin(angle) * distance;
}

void Camera::MovePosition(glm::fvec3 _offPos) {
	if (_offPos.z != 0) {
		this->pos.x += glm::sin(this->rot.y) * -1.0f * _offPos.z;
		this->pos.z += glm::cos(this->rot.y) * _offPos.z;
	}
	if (_offPos.x != 0) {
		this->pos.x += glm::sin(this->rot.y - 90) * -1.0f * _offPos.x;
		this->pos.z += glm::cos(this->rot.y - 90) * _offPos.x;
	}
	this->pos.y += _offPos.y;
}

void Camera::Rotate(float horizontal, double vertical) {
	this->rot.y += horizontal;
	this->rot.x += vertical;

	if (this->rot.y < 0) {
		this->rot.y += 360.0;
	}

	if (this->rot.y > 360.0) {
		this->rot.y -= 360.0;
	}

	if (this->rot.x < 0) {
		this->rot.x += 360.0;
	}

	if (this->rot.x > 360.0) {
		this->rot.x -= 360.0;
	}
}

glm::fmat4 Camera::GetViewMatrix() {
	glm::fmat4 viewmatrix(1.0f);
	float x = this->rot.x * (3.14f / 180.0f);
	float y = this->rot.y * (3.14f / 180.0f);
	viewmatrix = glm::rotate(viewmatrix, x, glm::vec3(1.0f, 0.0f, 0.0f));
	viewmatrix = glm::rotate(viewmatrix, y, glm::vec3(0.0f, 1.0f, 0.0f));
	viewmatrix = glm::translate(viewmatrix, this->pos);
	return viewmatrix;
}