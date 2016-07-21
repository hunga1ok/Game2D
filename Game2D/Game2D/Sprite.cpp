#include "Sprite.h"

Sprite::Sprite(): m_fVelocityY(0), m_fSlideTime(0)
{
}

Sprite::Sprite(std::vector<Texture*> textures, Model* model, vector<Animation*> listAniamtion, Shader* shader, SPRITETYPE spriteType)
	:Object(textures, model, listAniamtion, shader, OBJECT2D)
{
	m_spriteType = spriteType;
	m_fVelocityY = VELOCITY_Y;
	m_bisJumping = false;
	m_fSlideTime = SLIDETIME;
}

Sprite::~Sprite()
{
}


void Sprite::Move(float deltaTime)
{
	switch (m_objectState)
	{
	case RISING2:
		if (m_bisJumping)
		{
			m_bisJumping = false;
			m_fVelocityY += VELOCITY_Y / 2.f;
		}
		m_mMoveMatrix.SetTranslation(m_fSpeed*deltaTime, m_fSpeed*deltaTime*m_fVelocityY, 0);
		m_fVelocityY -= 9.8f*deltaTime;
		if (m_fVelocityY < 0)
			m_objectState = FALLING;
		break;
	case RISING:
		m_bisJumping = true;
		m_mMoveMatrix.SetTranslation(m_fSpeed*deltaTime, m_fSpeed*deltaTime*m_fVelocityY, 0);
		m_fVelocityY -= 9.8f*deltaTime;
		if (m_fVelocityY < 0)
			m_objectState = FALLING;
		break;
	case RUNNING:
		m_fVelocityY = VELOCITY_Y;
		m_mMoveMatrix.SetTranslation(m_fSpeed*deltaTime, 0, 0);
		break;
	case FALLING:
		m_bisJumping = false;
		m_mMoveMatrix.SetTranslation(m_fSpeed*deltaTime, m_fSpeed*deltaTime*m_fVelocityY, 0);
		m_fVelocityY -= 9.8f*deltaTime;
		if (m_v3position.y < 0)
		{
			m_mWorld.m[3][1] = 0;
			
			m_objectState = RUNNING;
		}
		break;
	case SLIDING:
		m_mMoveMatrix.SetTranslation(m_fSpeed*deltaTime, 0, 0);
		m_fSlideTime -= deltaTime;
		if (m_fSlideTime<0)
		{
			m_fSlideTime = SLIDETIME;
			m_objectState = RUNNING;
		}
		break;
	default:
		break;
	}
	m_mWorld = m_mWorld*m_mMoveMatrix;
	m_v3position = Vector3(m_mWorld.m[3][0], m_mWorld.m[3][1], m_mWorld.m[3][2]);
	//printf("%d:  %f, %f, %f\n",m_spriteType , m_v3position.x, m_v3position.y, m_v3position.z);
}

void Sprite::OnCollision()
{
}

void Sprite::Update(float deltaTime)
{
	m_animationTemp += m_fAnimatedSpeed*m_fSpeed*deltaTime;
	Move(deltaTime);
}
