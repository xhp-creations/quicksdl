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
	Texture* mInstructions;

	float mSpinAmount;

	bool mSpin;

public:

	ExampleScreen();
	~ExampleScreen();

	void SpinLogo(bool spin);
	void PlaySoundFX();

	void Update();

	void Render();
};
#endif