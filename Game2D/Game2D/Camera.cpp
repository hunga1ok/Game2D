#include "Camera.h"
Camera::Camera()
{
	m_mViewMatrix.SetIdentity();
	m_v3Up = Vector3(0, 1, 0);
	m_v3Position = Vector3(0, 0, 0);
	m_v3Target = Vector3(0, 0, 1);
}
Camera::Camera(float speed, float sensitivity)
	:m_fCameraSpeed(speed),m_fSensitivity(sensitivity)
{
	m_mViewMatrix.SetIdentity();
	m_v3Up = Vector3(0, 1, 0);
	m_v3Position = Vector3(0, 0, 0);
	m_v3Target = Vector3(0, 0, 1);
}
Camera::~Camera()
{
}

void Camera::CalculateViewMatrix()
{
	Vector3 zaxis = (m_v3Position - m_v3Target).Normalize();
	Vector3 xaxis = (m_v3Up.Cross(zaxis)).Normalize();
	Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();
	m_mViewMatrix.m[0][0] = xaxis.x;
	m_mViewMatrix.m[0][1] = yaxis.x;
	m_mViewMatrix.m[0][2] = zaxis.x;
	m_mViewMatrix.m[0][3] = 0;
	m_mViewMatrix.m[1][0] = xaxis.y;
	m_mViewMatrix.m[1][1] = yaxis.y;
	m_mViewMatrix.m[1][2] = zaxis.y;
	m_mViewMatrix.m[1][3] = 0;
	m_mViewMatrix.m[2][0] = xaxis.z;
	m_mViewMatrix.m[2][1] = yaxis.z;
	m_mViewMatrix.m[2][2] = zaxis.z;
	m_mViewMatrix.m[2][3] = 0;
	m_mViewMatrix.m[3][0] = -m_v3Position.Dot(xaxis);
	m_mViewMatrix.m[3][1] = -m_v3Position.Dot(yaxis);
	m_mViewMatrix.m[3][2] = -m_v3Position.Dot(zaxis);
	m_mViewMatrix.m[3][3] = 1;
}
void Camera::Move(Vector3 direction, float deltaTime)
{
	Vector3 deltaMove = Vector3(0, 0, 0);

	Vector3 zaxis = (m_v3Position - m_v3Target).Normalize();
	Vector3 xaxis = (m_v3Up.Cross(zaxis)).Normalize();
	Vector3 yaxis = (zaxis.Cross(xaxis)).Normalize();

	deltaMove += zaxis*direction.z + xaxis*direction.x + yaxis*direction.y;
	deltaMove *= deltaTime * m_fCameraSpeed;

	if (deltaMove.Length())
	{
		m_v3Position += deltaMove;
		m_v3Target += deltaMove;
	}
}
void Camera::Rotate(Vector3 direction)
{
	m_v3Target = m_v3Position + direction;
}

void Camera::SetSpeed(float speed)
{
	m_fCameraSpeed = speed;
}
float Camera::GetSpeed() const
{
	return m_fCameraSpeed;
}
void Camera::SetSensitivity(float sensitivity)
{
	m_fSensitivity = sensitivity;
}
float Camera::GetSensitivity() const
{
	return m_fSensitivity;
}
Matrix Camera::GetViewMatrix() const
{
	return m_mViewMatrix;
}

void Camera::SetPosition(Vector3 pos)
{
	m_v3Position = pos;
	m_v3Target = pos + Vector3(0, 0, -1);
}

Vector3 Camera::GetPosition() const
{
	return m_v3Position;
}




