#ifndef _EXAMPLESCREEN_H
#define _EXAMPLESCREEN_H
#include "AudioManager.h"
#include "InputManager.h"
#include "Texture.h"
#include "Timer.h"

using namespace QuickSDL;

class ExampleScreen : public GameEntity {

private:

	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;

	Texture* mLogo;
	Texture* mJoystickNum;
	int mNumJoysticks;
	Texture* mInstructions;
#ifdef __WIIU__
	Texture* mWiiUFontTest;
#endif

	Texture* mController;
	Texture* mControllerName;
	Texture* mButtons[16];
	Texture* mRedButton[2];

	bool mButtonsPressed[16];

	float mSpinAmount;
	bool mSpin;
	bool mShowJoystickStatus;
	int mSelectedJoystick;

	float mLeftx = 378.0f;
	float mLefty = 268.0f;
	float mLeftxChange;
	float mLeftyChange;
	float mRightx = 904.0f;
	float mRighty = 268.0f;
	float mRightxChange;
	float mRightyChange;

private:

	void AddControllerTextures();

	void SpinLogo(bool spin);
	void PlaySoundFX();
	void UpdateJoysticks(int joynum = 0);

public:

	ExampleScreen();
	~ExampleScreen();

	void Update();

	void Render();
};
#endif