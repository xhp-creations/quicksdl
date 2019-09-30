#include "ScreenManager.h"

ScreenManager* ScreenManager::sInstance = NULL;

ScreenManager* ScreenManager::Instance() {

	if (sInstance == NULL)
		sInstance = new ScreenManager();

	return sInstance;
}

void ScreenManager::Release() {

	delete sInstance;
	sInstance = NULL;
}

ScreenManager::ScreenManager() {

	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mExampleScreen = new ExampleScreen();

	mCurrentScreen = example;
}

ScreenManager::~ScreenManager() {

	mInput = NULL;

	delete mExampleScreen;
	mExampleScreen = NULL;
}

void ScreenManager::Update() {

	switch (mCurrentScreen) {

	case example:

		mExampleScreen->Update();
		break;

	case play:

		//mPlayScreen->Update();
		break;
	}
}

void ScreenManager::Render() {

	switch (mCurrentScreen) {

	case example:

		mExampleScreen->Render();
		break;

	case play:

		//mPlayScreen->Render();
		break;
	}
}