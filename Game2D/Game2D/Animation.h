#pragma once
#include "Utilities/utilities.h"
#include "AnimationProperties.h"

class Animation
{
public:
	Animation();
	Animation(AnimationProperties* listIndex,GLuint indexNumber, int id);
	~Animation();

	AnimationProperties* GetListIndex() const;
	void SetListIndex(AnimationProperties* listIndex);
	GLuint GetIndexNumber() const;
	void SetIndexNumber(GLuint num);
	int GetID() const;
	void SetID(int id);

private:
	AnimationProperties* m_listIndex;
	GLuint m_iIndexNumber;
	int m_iID;
};