#include "Object.h"
#include "ScenceManager.h"
Object::Object()
{
	Init();
}
Object::Object(vector<Texture*> textures, Model* model, vector<Animation*> listAniamtion, Shader* shader, OBJECTTYPE objType)
	:m_vListTextures(textures), m_vListAnimation(listAniamtion), m_model(model), m_shader(shader),m_objectType(objType)
{
	Init();
}
Object::~Object()
{
}

void Object::Init()
{
	m_mMVP.SetIdentity();
	m_mWorld.SetIdentity();
	m_mTranslate.SetIdentity();
	m_mScale.SetIdentity();
	m_mRotate.SetIdentity();
	m_fAnimatedSpeed = 100;
	m_fSpeed = 0.01;
	m_animationTemp = 0;
	m_objectState = RUNNING;
	if (m_vListAnimation.size() > 0)
		m_iNumberOfFrame = m_vListAnimation[m_objectState]->GetIndexNumber();
	else
		m_iNumberOfFrame = 1;

	AnimationOffset = new int[m_vListAnimation.size()];
	int temp = 0;
	for (int i= 0; i < m_vListAnimation.size(); i++)
	{
		AnimationOffset[i] = temp*16;
		temp += m_vListAnimation.at(i)->GetIndexNumber();
	}
}
void Object::Update(float deltaTime)
{
}

void Object::Move(float deltaTime)
{
	
}

void Object::OnCollision()
{
}

void Object::Draw()
{
	glUseProgram(m_shader->GetProgram());

	for (auto i = 0; i < m_vListTextures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		if (m_vListTextures[i]->GetType() == CUBEOBJECT)
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_vListTextures[i]->GetTextureId());
		else
			glBindTexture(GL_TEXTURE_2D, m_vListTextures[i]->GetTextureId());

		glUniform1i(m_shader->GetTextureUniforms()[i], i);
	}
	glUniform1f(m_shader->GetTimeUniform(), GetTickCount() % 1000 / 1000.f);

	glBindBuffer(GL_ARRAY_BUFFER, m_model->GetVboId());
	glBindBuffer(GL_ARRAY_BUFFER, m_model->GetVboId());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_model->GetIdoId());

	if (m_shader->GetPositionAttribute() != -1)
	{
		glVertexAttribPointer(m_shader->GetPositionAttribute(), 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<void *>(POSITION_OFFSET));
		glEnableVertexAttribArray(m_shader->GetPositionAttribute());
	}
	if (m_shader->GetMatrixUniform() != -1)
	{
		glUniformMatrix4fv(m_shader->GetMatrixUniform(), 1, GL_FALSE, GetMVP().m[0]);
	}
	if (m_shader->GetUVAttribute() != -1)
	{
		glVertexAttribPointer(m_shader->GetUVAttribute(), 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void *>(UV_OFFSET));
		glEnableVertexAttribArray(m_shader->GetUVAttribute());
	}
	int temp=0;
	if (m_vListAnimation.size())
	{
		m_iNumberOfFrame = m_vListAnimation[m_objectState]->GetIndexNumber();
		temp = AnimationOffset[m_objectState];
	}

//	glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_INT, reinterpret_cast<void *>(0));
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_INT, 
		reinterpret_cast<void *>(temp+16* (static_cast<int>(m_animationTemp) % m_iNumberOfFrame)));
//	glDrawArrays(GL_TRIANGLE_STRIP,8, 4);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
Matrix Object::GetMVP()
{
	Matrix per= ScenceManager::GetInstance()->GetPerspectiveMatrix();
	if (m_objectType == OBJECT2D)
		per.SetIdentity();
	m_mMVP = m_mWorld* (ScenceManager::GetInstance()->GetCamara()->GetViewMatrix())*per;
	return m_mMVP;
}

void Object::SetTranslate(Matrix translate)
{
	m_mTranslate = translate;
}
void Object::SetScale(Matrix scale)
{
	m_mScale = scale;
}
void Object::SetRotate(Matrix rotate)
{
	m_mRotate = rotate;
}
Matrix Object::GetWorldMatrix()
{
	m_mWorld = m_mWorld*m_mScale;
	m_mWorld = m_mWorld*m_mRotate;
	m_mWorld = m_mWorld*m_mTranslate;
	m_mScale.SetIdentity();
	m_mRotate.SetIdentity();
	m_mTranslate.SetIdentity();
	return m_mWorld;
}
void Object::SetObjectId(GLuint objectId)
{
	m_iObjectId = objectId;
}
GLuint Object::GetObjectId() const
{
	return m_iObjectId;
}

Model* Object::GetModel() const
{
	return m_model;
}

vector<Animation*> Object::GetListAnimation() const
{
	return m_vListAnimation;
}

float Object::GetAnimatedSpeed() const
{
	return m_fAnimatedSpeed;
}

void Object::SetAnimatedSpeed(float speed)
{
	m_fAnimatedSpeed = speed;
}

float Object::GetSpeed() const
{
	return m_fSpeed;
}

void Object::SetSpeed(float speed)
{
	m_fSpeed = speed;
}

Vector3 Object::GetPosition() const
{
	return m_v3position;
}

OBJECTSTATE Object::GetObjectState() const
{
	return m_objectState;
}

void Object::SetObjectState(OBJECTSTATE state)
{
	m_objectState = state;
}

SPRITETYPE Object::GetSpriteType() const
{
	return m_spriteType;
}

void Object::SetSpriteType(SPRITETYPE type)
{
	m_spriteType = type;
}

bool Object::IsJumping() const
{
	return m_bisJumping;
}

void Object::IsJumping(bool b)
{
	m_bisJumping = b;
}
