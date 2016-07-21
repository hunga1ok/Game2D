#pragma once
#include "Utilities/utilities.h"
class Camera
{
public:
	Camera();
	Camera(float speed, float sensitivity);
	~Camera();

	void SetSpeed(float speed);
	float GetSpeed() const;
	void SetSensitivity(float sensitivity);
	float GetSensitivity() const;
	Matrix GetViewMatrix() const;
	void SetPosition(Vector3 pos);
	Vector3 GetPosition() const;

	void CalculateViewMatrix();
	void Move(Vector3 direction, float deltaTime);
	void Rotate(Vector3 direction);
private:
	float m_fCameraSpeed, m_fSensitivity;
	Matrix m_mViewMatrix;
	Vector3 m_v3Position, m_v3Target, m_v3Up;
};