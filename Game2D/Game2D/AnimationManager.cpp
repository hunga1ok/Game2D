#include "AnimationManager.h"

AnimationManager* AnimationManager::s_Instance = nullptr;
AnimationManager::AnimationManager()
{
}

AnimationManager::~AnimationManager()
{
}

AnimationManager* AnimationManager::GetInstance()
{
	return s_Instance;
}

void AnimationManager::CreateInstance()
{
	if (!s_Instance)
		s_Instance = new AnimationManager();
}

void AnimationManager::DestroyInstance()
{
	if (s_Instance)
		delete s_Instance;
}

void AnimationManager::Init(char* fileName)
{
	FILE* f = fopen(fileName, "r");
	if (f)
	{
		int animationCount, id, indexCount, x, y, w, h, tw, th;
		AnimationProperties* listIndex = nullptr;
		fscanf(f, "ANIMATIONCOUNT %d\n", &animationCount);
		for (auto i = 0; i < animationCount; i++)
		{
			fscanf(f, "ID %d\n", &id);
			fscanf(f, "INDEXCOUNT %d\n", &indexCount);
			listIndex = new AnimationProperties[indexCount];
			for (auto j = 0; j < indexCount; j++)
			{
				fscanf(f, "INDEX: %d, %d, %d, %d, %d, %d\n", &x, &y, &w, &h, &tw, &th);
				listIndex[j] = AnimationProperties(x, y, w, h, tw, th);
			}
			Animation *a = new Animation(listIndex, indexCount, id);
			m_vListAnimation.push_back(a);
		}		
	}
}

Animation* AnimationManager::FindAnimationById(int Id)
{
	for (auto i : m_vListAnimation)
	{
		if (i->GetID() == Id)
			return  i;
	}
	return nullptr;
}
