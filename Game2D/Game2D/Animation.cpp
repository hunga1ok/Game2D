#include "Animation.h"

Animation::Animation()
{
}

Animation::Animation(AnimationProperties* listIndex, GLuint indexNumber,int id)
	: m_listIndex(listIndex), m_iIndexNumber(indexNumber), m_iID(id)
{
}

Animation::~Animation()
{
	delete[] m_listIndex;
}

AnimationProperties* Animation::GetListIndex() const
{
	return m_listIndex;
}

void Animation::SetListIndex(AnimationProperties* listIndex)
{
	m_listIndex = listIndex;
}

GLuint Animation::GetIndexNumber() const
{
	return m_iIndexNumber;
}

void Animation::SetIndexNumber(GLuint num)
{
	m_iIndexNumber = num;
}

int Animation::GetID() const
{
	return m_iID;
}

void Animation::SetID(int id)
{
	m_iID = id;
}
