#pragma once

enum OBJECTTYPE { OBJECT2D, OBJECT3D, CUBEOBJECT, TERRAIN, ENDO };
enum SPRITETYPE { RAT, CAT, TRAP, ITEM, BACKGROUND, ENDS };
enum  KEY { UP, DOWN, LEFT, RIGHT, SPECIAL, ENDK };
enum OBJECTSTATE { RUNNING, RISING, RISING2, FALLING, SLIDING, ENDOS };
class Globals
{
public:
	static const int screenWidth = 960;
	static const int screenHeight = 720;
};
