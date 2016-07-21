#pragma once
#include "Utilities/utilities.h"
#include "Animation.h"
#include <stdio.h>
#include <vector>
#include  "AnimationProperties.h"
using namespace std;
class AnimationManager
{
public:
	AnimationManager();
	~AnimationManager();

	static  AnimationManager* GetInstance();
	static void CreateInstance();
	static void DestroyInstance();

	void Init(char *fileName);
	Animation* FindAnimationById(int Id);
	
private:
	static AnimationManager* s_Instance;
	vector<Animation*> m_vListAnimation;

};