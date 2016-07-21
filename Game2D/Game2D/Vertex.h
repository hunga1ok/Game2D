#pragma once
#include "Utilities/Math.h"

struct Vertex
{
	Vector3 position;
	Vector3 normal;
	Vector3 binormal;
	Vector3 tangent;
	Vector2 uv;
};

#define POSITION_OFFSET nullptr
#define MORMAL_OFFSET 12
#define BIMORMAL_OFFSET 24
#define TANGENT_OFFSET 36
#define UV_OFFSET 48