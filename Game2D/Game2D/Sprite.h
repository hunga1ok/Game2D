#pragma once
#include "Object.h"
#define VELOCITY_Y 4
#define SLIDETIME 1

class Sprite :public Object
{
public:
	Sprite();
	Sprite(std::vector<Texture*>  textures, Model *model, vector<Animation*> listAniamtion, Shader *shader, SPRITETYPE spriteType);
	~Sprite();

	void Move(float deltaTime) override;
	void OnCollision() override;
	void Update(float deltaTime) override;
private:
	float m_fVelocityY;
	float m_fSlideTime;
};