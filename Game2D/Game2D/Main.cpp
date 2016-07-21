#include "Utilities/utilities.h"
#include "Globals.h"
#include <conio.h>
#include <stdio.h>
#include "ScenceManager.h"
#include "ResourceManager.h"
#include "AnimationManager.h"

int Init(ESContext *esContext)
{
	glClearColor(.0f, .0f, .0f, 0.0f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ResourceManager::CreateInstance();
	ResourceManager::GetInstance()->Init("../Resources/ResourceManager.txt");
	AnimationManager::CreateInstance();
	AnimationManager::GetInstance()->Init("../Resources/AnimationManager.txt");
	ScenceManager::CreateInstance();
	ScenceManager::GetInstance()->Init("../Resources/ScenceManager.txt");

	return 0;
}

void Draw(ESContext *esContext)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ScenceManager::GetInstance()->Draw();

	eglSwapBuffers(esContext->eglDisplay, esContext->eglSurface);
}

void Update(ESContext *esContext, float deltaTime)
{
	ScenceManager::GetInstance()->Update(deltaTime);
}

void Key(ESContext *esContext, unsigned char key, bool bIsPressed)
{
	int a = ScenceManager::GetInstance()->GetMainCharater()->GetObjectState();
	if (bIsPressed)
		switch (key)
		{
		case 'W':
			if (a == RISING)
				ScenceManager::GetInstance()->GetMainCharater()->SetObjectState(RISING2);
			else
				if (a == RUNNING || a == SLIDING)
					ScenceManager::GetInstance()->GetMainCharater()->SetObjectState(RISING);
			break;
		case 'S':
			if (a==RUNNING)
			ScenceManager::GetInstance()->GetMainCharater()->SetObjectState(SLIDING);
			break;
		case 'A':
			break;
		case 'D':
			break;
		default:
			break;
		}
	//	else
	//		ScenceManager::GetInstance()->GetMainCharater()->SetObjectState(RUNNING);
}
void TouchActionDown(ESContext *esContext, int x, int y)
{

}

void TouchActionUp(ESContext *esContext, int x, int y)
{
}

void TouchActionMove(ESContext *esContext, int x, int y)
{

}

void CleanUp()
{
}


int main(int argc, char* argv[])
{

	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow(&esContext, "Game2D", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if (Init(&esContext) != 0)
		return 0;

	esRegisterDrawFunc(&esContext, Draw);
	esRegisterUpdateFunc(&esContext, Update);
	esRegisterKeyFunc(&esContext, Key);
	esRegisterMouseDownFunc(&esContext, TouchActionDown);
	esRegisterMouseUpFunc(&esContext, TouchActionUp);
	esRegisterMouseMoveFunc(&esContext, TouchActionMove);
	esMainLoop(&esContext);

	//releasing OpenGL resources
	CleanUp();

	//identifying memory leaks
	MemoryDump();
	printf("Press any key...\n");
	_getch();

	return 0;
}

