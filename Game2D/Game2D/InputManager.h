#pragma once
#include "Utilities/utilities.h"
#include <math.h>
#include "ScenceManager.h"
#include "Globals.h"
struct Point
{
	Point();
	Point(int x, int y);
	int x, y;
};
class InputManager
{
public:
	InputManager();
	~InputManager();

	static void CreateInstance();
	static  InputManager* GetInstance();
	static void DestroyInstance();

	void SetLastMousePoint(Point p);
	Point GetLastMousePoint() const;
	void SetCurrentMousePoint(Point p);
	Point GetCurrentMousePoint() const;
	void isMouseDown(bool bl);
	bool isMouseDown() const;
	void isKeyPressed(KEY key,bool bl);
	
	Vector3 GetRotateDirection();
	Vector3 GetMoveDirection();

private:
	static InputManager* s_Instance;
	GLfloat yaw = 90.0f;
	GLfloat pitch = 0.0f;
	Point m_lastMousePoint, m_curerntMousePoint;
	bool m_isKeysPressed[ENDK];
	bool m_isMouseDowm;
};