#pragma once

struct AnimationProperties
{
	AnimationProperties() {};
	AnimationProperties(int x, int y, int w, int h, int tw, int th)
		: spriteX(x), spriteY(y), spriteW(w), spriteH(h), textureW(tw), textureH(th) {};
	int spriteX;
	int spriteY;
	int spriteW;
	int spriteH;
	int textureW;
	int textureH;
};