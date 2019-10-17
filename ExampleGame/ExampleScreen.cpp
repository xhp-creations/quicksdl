#include"ExampleScreen.h"

ExampleScreen::ExampleScreen() {

	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();

	mLogo = new Texture("4TU.png");
	mLogo->Scale(Vector2(5.0f, 5.0f));
	mLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.45f));
	mLogo->Parent(this);

	mNumJoysticks = mInput->NumAttachedJoysticks();
	std::string str = std::to_string(mNumJoysticks);
	mJoystickNum = new Texture("Number of Joysticks: " + str + " - Press START and L (1) for Joystick Status Screen", "IBMPlexSans-SemiBold.ttf", 32, RGB_white_dull);
	mJoystickNum->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.04f));
	mJoystickNum->Parent(this);

	mInstructions = new Texture("Press A button to spin logo or B button to play SFX", "IBMPlexSans-SemiBold.ttf", 32, RGB_white_dull);
	mInstructions->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.95f));
	mInstructions->Parent(this);

#ifdef __WIIU__
	mWiiUFontTest = new Texture("Wii U System Font Test", 24, RGB_white_dull);
	mWiiUFontTest->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.88f));
	mWiiUFontTest->Parent(this);
#endif

	AddControllerTextures();

	mSpinAmount = 0.0f;
	mSpin = false;
	mShowJoystickStatus = false;
	mSelectedJoystick = 0;

	for (int i = 0; i < 2; i++) {
		mRedButton[i] = new Texture("redbutton.png");
		mRedButton[i]->Pos(Vector2(0.0f, 0.0f));
		mRedButton[i]->Parent(this);
	}

	Graphics::Instance()->SetDrawColor(RGB_tomato);
}

ExampleScreen::~ExampleScreen() {

	delete mLogo;
	mLogo = NULL;

	delete mJoystickNum;
	mJoystickNum = NULL;

	delete mInstructions;
	mInstructions = NULL;

#ifdef __WIIU__
	delete mWiiUFontTest;
	mWiiUFontTest = NULL;
#endif

	delete mController;
	mController = NULL;
	delete mControllerName;
	mControllerName = NULL;

	for (int i = 0; i < 16; i++) {

		delete mButtons[i];
		mButtons[i] = NULL;
	}

	for (int i = 0; i < 2; i++) {

		delete mRedButton[i];
		mRedButton[i] = NULL;
	}
}

void ExampleScreen::AddControllerTextures() {

	mController = new Texture("BlackProController1.png");
	mController->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mController->Parent(this);

	std::string str = "Controller Name";
	mControllerName = new Texture(str, "IBMPlexSans-SemiBold.ttf", 32, RGB_white_dull);
	mControllerName->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.95f));
	mControllerName->Parent(this);

	mButtons[0] = new Texture("ProControllerA.png");
	mButtons[0]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mButtons[0]->Parent(this);

	mButtons[1] = new Texture("ProControllerB.png");
	mButtons[1]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mButtons[1]->Parent(this);

	mButtons[2] = new Texture("ProControllerX.png");
	mButtons[2]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mButtons[2]->Parent(this);

	mButtons[3] = new Texture("ProControllerY.png");
	mButtons[3]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mButtons[3]->Parent(this);

	mButtons[4] = new Texture("ProControllerLStick.png");
	mButtons[4]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mButtons[4]->Parent(this);

	mButtons[5] = new Texture("ProControllerRStick.png");
	mButtons[5]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mButtons[5]->Parent(this);

	mButtons[6] = new Texture("ProControllerL.png");
	mButtons[6]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mButtons[6]->Parent(this);

	mButtons[7] = new Texture("ProControllerR.png");
	mButtons[7]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mButtons[7]->Parent(this);

	mButtons[8] = new Texture("ProControllerZL.png");
	mButtons[8]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mButtons[8]->Parent(this);

	mButtons[9] = new Texture("ProControllerZR.png");
	mButtons[9]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mButtons[9]->Parent(this);

	mButtons[10] = new Texture("ProControllerStart.png");
	mButtons[10]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mButtons[10]->Parent(this);

	mButtons[11] = new Texture("ProControllerSelect.png");
	mButtons[11]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mButtons[11]->Parent(this);

	mButtons[12] = new Texture("ProControllerLeft.png");
	mButtons[12]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mButtons[12]->Parent(this);

	mButtons[13] = new Texture("ProControllerUp.png");
	mButtons[13]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mButtons[13]->Parent(this);

	mButtons[14] = new Texture("ProControllerRight.png");
	mButtons[14]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mButtons[14]->Parent(this);

	mButtons[15] = new Texture("ProControllerDown.png");
	mButtons[15]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mButtons[15]->Parent(this);

}

void ExampleScreen::SpinLogo(bool spin) {

	mSpin = spin;
}

void ExampleScreen::PlaySoundFX() {

	mAudio->PlaySFX("sfx.wav");
}

void ExampleScreen::UpdateJoysticks(int joynum) {

	if (!mShowJoystickStatus) {
		std::string str = std::to_string(mNumJoysticks);
		mJoystickNum = new Texture("Number of Joysticks: " + str + " - Press START and L (1) for Joystick Status Screen", "IBMPlexSans-SemiBold.ttf", 32, RGB_white_dull);
		mJoystickNum->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.04f));
		mJoystickNum->Parent(this);
	}
	else {

		mJoystickNum = new Texture("Press BACK and R (2) for Previous Screen", "IBMPlexSans-SemiBold.ttf", 32, RGB_white_dull);
		mJoystickNum->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.04f));
		mJoystickNum->Parent(this);

		std::string str = mInput->JoyStickName(joynum);
		mControllerName = new Texture(str, "IBMPlexSans-SemiBold.ttf", 32, RGB_white_dull);
		mControllerName->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.95f));
		mControllerName->Parent(this);

#ifdef __WIIU__
		if (joynum == 0) {

			str = "BlackProController0.png";
		} else {

			std::size_t found = str.find_last_of("#");
			std::string channel = str.substr(found + 1, 1);
			str = "BlackProController" + channel + ".png";
		}
#else
		std::size_t found = str.find_last_of("#");
		std::string channel = str.substr(found + 1, 1);

		str = "BlackProController" + channel + ".png";
#endif
		mController = new Texture(str);
		mController->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
		mController->Parent(this);
	}
}

void ExampleScreen::Update() {

	int num = mInput->NumAttachedJoysticks();
	if (num != mNumJoysticks) {

		mNumJoysticks = num;
		UpdateJoysticks();
	}

	for (int i = 0; i < mNumJoysticks; i++) {
#ifndef __WIIU__
		if (mInput->JoyButtonDown(XINPUT_LB, i) && mInput->JoyButtonDown(XINPUT_START, i)) {
#else
		if (mInput->JoyButtonDown(WIIU_JOY_L, i) && mInput->JoyButtonDown(WIIU_JOY_PLUS, i)) {
#endif

			mShowJoystickStatus = true;
			mSelectedJoystick = i;
			UpdateJoysticks();
		}
#ifndef __WIIU__
		if (mInput->JoyButtonDown(XINPUT_A, mSelectedJoystick)) {
#else
		if (mInput->JoyButtonDown(WIIU_JOY_A, mSelectedJoystick)) {
#endif

			mButtonsPressed[0] = true;
		} else {

			mButtonsPressed[0] = false;
		}
#ifndef __WIIU__
		if (mInput->JoyButtonDown(XINPUT_B, mSelectedJoystick)) {
#else
		if (mInput->JoyButtonDown(WIIU_JOY_B, mSelectedJoystick)) {
#endif

			mButtonsPressed[1] = true;
		}
		else {

			mButtonsPressed[1] = false;
		}
#ifndef __WIIU__
		if (mInput->JoyButtonDown(XINPUT_X, mSelectedJoystick)) {
#else
		if (mInput->JoyButtonDown(WIIU_JOY_X, mSelectedJoystick)) {
#endif

			mButtonsPressed[2] = true;
		}
		else {

			mButtonsPressed[2] = false;
		}
#ifndef __WIIU__
		if (mInput->JoyButtonDown(XINPUT_Y, mSelectedJoystick)) {
#else
		if (mInput->JoyButtonDown(WIIU_JOY_Y, mSelectedJoystick)) {
#endif

			mButtonsPressed[3] = true;
		}
		else {

			mButtonsPressed[3] = false;
		}
#ifndef __WIIU__
		if (mInput->JoyButtonDown(XINPUT_L_THUMB, mSelectedJoystick)) {
#else
		if (mInput->JoyButtonDown(WIIU_JOY_L_THUMB, mSelectedJoystick)) {
#endif

			mButtonsPressed[4] = true;
		}
		else {

			mButtonsPressed[4] = false;
		}
#ifndef __WIIU__
		if (mInput->JoyButtonDown(XINPUT_R_THUMB, mSelectedJoystick)) {
#else
		if (mInput->JoyButtonDown(WIIU_JOY_R_THUMB, mSelectedJoystick)) {
#endif

			mButtonsPressed[5] = true;
		}
		else {

			mButtonsPressed[5] = false;
		}
#ifndef __WIIU__
		if (mInput->JoyButtonDown(XINPUT_LB, mSelectedJoystick)) {
#else
		if (mInput->JoyButtonDown(WIIU_JOY_L, mSelectedJoystick)) {
#endif

			mButtonsPressed[6] = true;
		}
		else {

			mButtonsPressed[6] = false;
		}
#ifndef __WIIU__
		if (mInput->JoyButtonDown(XINPUT_RB, mSelectedJoystick)) {
#else
		if (mInput->JoyButtonDown(WIIU_JOY_R, mSelectedJoystick)) {
#endif

			mButtonsPressed[7] = true;
		}
		else {

			mButtonsPressed[7] = false;
		}
#ifndef __WIIU__
		if (mInput->JoyAxisDown(InputManager::left_trigger, InputManager::trigger_down, mSelectedJoystick)) {
#else
		if (mInput->JoyButtonDown(WIIU_JOY_ZL, mSelectedJoystick)) {
#endif

			mButtonsPressed[8] = true;
		}
		else {

			mButtonsPressed[8] = false;
		}
#ifndef __WIIU__
		if (mInput->JoyAxisDown(InputManager::right_trigger, InputManager::trigger_down, mSelectedJoystick)) {
#else
		if (mInput->JoyButtonDown(WIIU_JOY_ZR, mSelectedJoystick)) {
#endif

			mButtonsPressed[9] = true;
		}
		else {

			mButtonsPressed[9] = false;
		}
#ifndef __WIIU__
		if (mInput->JoyButtonDown(XINPUT_START, mSelectedJoystick)) {
#else
		if (mInput->JoyButtonDown(WIIU_JOY_PLUS, mSelectedJoystick)) {
#endif

			mButtonsPressed[10] = true;
		}
		else {

			mButtonsPressed[10] = false;
		}
#ifndef __WIIU__
		if (mInput->JoyButtonDown(XINPUT_BACK, mSelectedJoystick)) {
#else
		if (mInput->JoyButtonDown(WIIU_JOY_MINUS, mSelectedJoystick)) {
#endif

			mButtonsPressed[11] = true;
		}
		else {

			mButtonsPressed[11] = false;
		}
#ifndef __WIIU__
		if (mInput->JoyHatDown(InputManager::hat_left, mSelectedJoystick)) {
#else
		if (mInput->JoyButtonDown(WIIU_JOY_DPAD_LEFT, mSelectedJoystick)) {
#endif

			mButtonsPressed[12] = true;
		}
		else {

			mButtonsPressed[12] = false;
		}
#ifndef __WIIU__
		if (mInput->JoyHatDown(InputManager::hat_up, mSelectedJoystick)) {
#else
		if (mInput->JoyButtonDown(WIIU_JOY_DPAD_UP, mSelectedJoystick)) {
#endif

			mButtonsPressed[13] = true;
		}
		else {

			mButtonsPressed[13] = false;
		}
#ifndef __WIIU__
		if (mInput->JoyHatDown(InputManager::hat_right, mSelectedJoystick)) {
#else
		if (mInput->JoyButtonDown(WIIU_JOY_DPAD_RIGHT, mSelectedJoystick)) {
#endif

			mButtonsPressed[14] = true;
		}
		else {

			mButtonsPressed[14] = false;
		}
#ifndef __WIIU__
		if (mInput->JoyHatDown(InputManager::hat_down, mSelectedJoystick)) {
#else
		if (mInput->JoyButtonDown(WIIU_JOY_DPAD_DOWN, mSelectedJoystick)) {
#endif

			mButtonsPressed[15] = true;
		}
		else {

			mButtonsPressed[15] = false;
		}
#ifndef __WIIU__
		mLeftxChange = (mInput->JoyAxis(InputManager::left_joy_x, mSelectedJoystick) / 150.0f);
		mLeftyChange = (mInput->JoyAxis(InputManager::left_joy_y, mSelectedJoystick) / 150.0f);
		mRedButton[0]->Pos(Vector2(mLeftx + mLeftxChange, mLefty + mLeftyChange));
		mRightxChange = (mInput->JoyAxis(InputManager::right_joy_x, mSelectedJoystick) / 150.0f);
		mRightyChange = (mInput->JoyAxis(InputManager::right_joy_y, mSelectedJoystick) / 150.0f);
		mRedButton[1]->Pos(Vector2(mRightx + mRightxChange, mRighty + mRightyChange));
#else
		mLeftxChange = (mInput->JoyAxis(InputManager::left_wiiu_joy_x, mSelectedJoystick) / 150.0f);
		mLeftyChange = (mInput->JoyAxis(InputManager::left_wiiu_joy_y, mSelectedJoystick) / 150.0f);
		mRedButton[0]->Pos(Vector2(mLeftx + mLeftxChange, mLefty + mLeftyChange));
		mRightxChange = (mInput->JoyAxis(InputManager::right_wiiu_joy_x, mSelectedJoystick) / 150.0f);
		mRightyChange = (mInput->JoyAxis(InputManager::right_wiiu_joy_y, mSelectedJoystick) / 150.0f);
		mRedButton[1]->Pos(Vector2(mRightx + mRightxChange, mRighty + mRightyChange));
#endif
	}

	if (mShowJoystickStatus) {

		for (int i = 0; i < mNumJoysticks; i++) {
#ifndef __WIIU__
			if (mInput->JoyButtonDown(XINPUT_RB, i) && mInput->JoyButtonDown(XINPUT_BACK, i)) {
#else
			if (mInput->JoyButtonDown(WIIU_JOY_R, i) && mInput->JoyButtonDown(WIIU_JOY_MINUS, i)) {
#endif

				mShowJoystickStatus = false;
			}
		}

		UpdateJoysticks(mSelectedJoystick);
	} else {

		UpdateJoysticks();

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
}

void ExampleScreen::Render() {

	if (!mShowJoystickStatus) {
		mLogo->Render();
		mInstructions->Render();
#ifdef __WIIU__
		mWiiUFontTest->Render();
#endif
	} else {
	
		mController->Render();
		mControllerName->Render();

		for (int i = 0; i < 16; i++) {

			if (mButtonsPressed[i])
				mButtons[i]->Render();
		}

		Graphics::Instance()->DrawLine(mLeftx, mLefty, mLeftx + mLeftxChange, mLefty + mLeftyChange);
		Graphics::Instance()->DrawLine(mLeftx - 1, mLefty, mLeftx + mLeftxChange - 1, mLefty + mLeftyChange);
		Graphics::Instance()->DrawLine(mLeftx, mLefty - 1, mLeftx + mLeftxChange, mLefty + mLeftyChange - 1);
		Graphics::Instance()->DrawLine(mLeftx - 1, mLefty - 1, mLeftx + mLeftxChange - 1, mLefty + mLeftyChange - 1);
		Graphics::Instance()->DrawLine(mLeftx + 1, mLefty, mLeftx + mLeftxChange + 1, mLefty + mLeftyChange);
		Graphics::Instance()->DrawLine(mLeftx, mLefty + 1, mLeftx + mLeftxChange, mLefty + mLeftyChange + 1);
		Graphics::Instance()->DrawLine(mLeftx + 1, mLefty + 1, mLeftx + mLeftxChange + 1, mLefty + mLeftyChange + 1);
		mRedButton[0]->Render();
		Graphics::Instance()->DrawLine(mRightx, mRighty, mRightx + mRightxChange, mRighty + mRightyChange);
		Graphics::Instance()->DrawLine(mRightx - 1, mRighty, mRightx + mRightxChange - 1, mRighty + mRightyChange);
		Graphics::Instance()->DrawLine(mRightx, mRighty - 1, mRightx + mRightxChange, mRighty + mRightyChange - 1);
		Graphics::Instance()->DrawLine(mRightx - 1, mRighty - 1, mRightx + mRightxChange - 1, mRighty + mRightyChange - 1);
		Graphics::Instance()->DrawLine(mRightx + 1, mRighty, mRightx + mRightxChange + 1, mRighty + mRightyChange);
		Graphics::Instance()->DrawLine(mRightx, mRighty + 1, mRightx + mRightxChange, mRighty + mRightyChange + 1);
		Graphics::Instance()->DrawLine(mRightx + 1, mRighty + 1, mRightx + mRightxChange + 1, mRighty + mRightyChange + 1);
		mRedButton[1]->Render();
	}

	mJoystickNum->Render();
}