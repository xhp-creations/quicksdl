#include"ExampleScreen.h"

ExampleScreen::ExampleScreen() {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mLogo = new Texture("4TU.png");
	mLogo->Scale(Vector2(5.0f, 5.0f));
	mLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.45f));
	mLogo->Parent(this);

	mInstructions = new Texture("Press A button to spin logo or B button to play SFX", "IBMPlexSans-SemiBold.ttf", 32, RGB_white_dull);
	mInstructions->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.95f));
	mInstructions->Parent(this);

	float mSpinAmount = 0.0f;

	bool mSpin = false;
}

ExampleScreen::~ExampleScreen() {

	delete mLogo;
	mLogo = NULL;

	delete mInstructions;
	mInstructions = NULL;
}

void ExampleScreen::SpinLogo(bool spin) {

	mSpin = spin;
}

void ExampleScreen::PlaySoundFX() {

	mAudio->PlaySFX("sfx.wav");
}

void ExampleScreen::Update() {

#ifndef __WIIU__
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE) || mInput->JoyButtonPressed(XINPUT_A)) {
#else
	if (mInput->JoyButtonPressed(WIIU_JOY_A)) {
#endif

		SpinLogo(true);
	}
#ifndef __WIIU__
	else if (mInput->KeyPressed(SDL_SCANCODE_RALT) || mInput->JoyButtonPressed(XINPUT_B)) {
#else
	else if (mInput->JoyButtonPressed(WIIU_JOY_B)) {
#endif

		PlaySoundFX();
	}

	if (mSpin) {

		mSpinAmount += 6.0f * mTimer->DeltaTime();
		mLogo->Rotate(mSpinAmount);
	}

	if (mSpin && (mLogo->Rotation() > 359.0f)) {
		
		SpinLogo(false);
		mLogo->Rotate(-mLogo->Rotation());
		mSpinAmount = 0.0f;
		mAudio->PlaySFX("sfx2.wav");
	}
}

void ExampleScreen::Render() {

	mLogo->Render();

	mInstructions->Render();
}