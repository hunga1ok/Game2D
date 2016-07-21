#include "InputManager.h"
Point::Point()
{
}

Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
}
InputManager* InputManager::s_Instance = nullptr;
InputManager::InputManager(): m_isMouseDowm(false) {

}

InputManager::~InputManager()
{

}
void InputManager::CreateInstance()
{
	if (!s_Instance)
		s_Instance = new InputManager();
}
InputManager* InputManager::GetInstance()
{
	return s_Instance;
}
void InputManager::DestroyInstance()
{
	if (s_Instance)
	delete s_Instance;
}
void InputManager::SetLastMousePoint(Point p)
{
	m_lastMousePoint = p;
}
Point InputManager::GetLastMousePoint() const
{
	return m_lastMousePoint;
}
void InputManager::SetCurrentMousePoint(Point p)
{
	m_curerntMousePoint = p;
}
Point InputManager::GetCurrentMousePoint() const
{
	return m_curerntMousePoint;
}
void InputManager::isMouseDown(bool bl)
{
	m_isMouseDowm = bl;
}
bool InputManager::isMouseDown() const
{
	return m_isMouseDowm;
}
void InputManager::isKeyPressed(KEY key, bool bl)
{
	m_isKeysPressed[key] = bl;
}
Vector3 InputManager::GetRotateDirection()
{
	int offsetx = m_curerntMousePoint.x - m_lastMousePoint.x;
	int offsety = m_lastMousePoint.y - m_curerntMousePoint.y;
	m_lastMousePoint.x = m_curerntMousePoint.x;
	m_lastMousePoint.y = m_curerntMousePoint.y;

	float sensitivity = ScenceManager::GetInstance()->GetCamara()->GetSensitivity();
	offsetx *= sensitivity;
	offsety *= sensitivity;

	yaw += offsetx;
	pitch += offsety;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	Vector3 front;
	front.x = cos(yaw*3.14 / 180) * cos(pitch*3.14 / 180);
	front.y = sin(pitch*3.14 / 180);
	front.z = sin(yaw*3.14 / 180) * cos(pitch*3.14 / 180);
	return front.Normalize();
}
Vector3 InputManager::GetMoveDirection()
{
	Vector3 direction = Vector3(m_isKeysPressed[RIGHT] - m_isKeysPressed[LEFT], 0, m_isKeysPressed[DOWN] - m_isKeysPressed[UP]);
	return direction;
}








