#ifndef _SCREENMANAGER_H
#define _SCREENMANAGER_H
#include "InputManager.h"
#include "AudioManager.h"
#include "ExampleScreen.h"
//#include "PlayScreen.h"

using namespace QuickSDL;

class ScreenManager {

private:

	enum SCREENS { example, play };

	static ScreenManager* sInstance;

	InputManager* mInput;
	AudioManager* mAudio;

	ExampleScreen* mExampleScreen;
	//PlayScreen* mPlayScreen;

	SCREENS mCurrentScreen;

public:

	static ScreenManager* Instance();
	static void Release();

	void Update();
	void Render();

private:

	ScreenManager();
	~ScreenManager();
};
#endif