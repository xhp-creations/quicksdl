//---------------------------------------------------------------------//
// InputManager.cpp                                                    //
// Handles all Input related functionality for keyboard and mouse.     //
//(To be expanded later to handle touch and contoller input)           //
//---------------------------------------------------------------------//
#include <string.h>
//---------------------------------------------------------------
#include "InputManager.h"
//---------------------------------------------------------------
// QuickSDL
//---------------------------------------------------------------
namespace QuickSDL {
	//Initializing to NULL
	InputManager* InputManager::sInstance = NULL;

	InputManager* InputManager::Instance() {

		//Create a new instance if no instance was created before
		if (sInstance == NULL)
			sInstance = new InputManager();

		return sInstance;
	}

	void InputManager::Release() {

		delete sInstance;
		sInstance = NULL;
	}

	InputManager::InputManager() {

		SDL_Init(SDL_INIT_JOYSTICK);

		FindAttachedJoysticks();

		mKeyboardState = SDL_GetKeyboardState(&mKeyLength);
		//Setting mPrevKeyboardState to be the same length as mKeyboardState
		mPrevKeyboardState = new Uint8[mKeyLength];
		//Copying the contents of mKeyboardState into mPrevKeyboardState so that it contains data on the first frame
		memcpy(mPrevKeyboardState, mKeyboardState, mKeyLength);
	}

	InputManager::~InputManager() {

		//Clearing the previous keyboard state array
		delete[] mPrevKeyboardState;
		mPrevKeyboardState = NULL;

		//delete[] mPrevJoyButtonState;
		//mPrevJoyButtonState = NULL;

		//mJoyButtonState = NULL;

		//delete[] mPrevJoyAxisState;
		//mPrevJoyAxisState = NULL;

		//mJoyAxisState = NULL;
	}

	bool InputManager::KeyDown(SDL_Scancode scanCode) {

		return (mKeyboardState[scanCode] != 0);
	}

	bool InputManager::KeyPressed(SDL_Scancode scanCode) {

		//returning true of the key was not pressed in the previous keyboard state but is pressed in the current one
		return (mPrevKeyboardState[scanCode]) == 0 && (mKeyboardState[scanCode] != 0);
	}

	bool InputManager::KeyReleased(SDL_Scancode scanCode) {

		//returning true of the key was pressed in the previous keyboard state but is not pressed in the current one
		return (mPrevKeyboardState[scanCode] != 0) && (mKeyboardState[scanCode] == 0);
	}

	bool InputManager::JoyButtonDown(int button, int joynum) {

		if (joy[joynum] != NULL)
			return (mJoyButtonState[joynum][button] != 0);
		else
			return false;
	}

	bool InputManager::JoyButtonPressed(int button, int joynum) {

		if (joy[joynum] != NULL)
			return (mPrevJoyButtonState[joynum][button]) == 0 && (mJoyButtonState[joynum][button] != 0);
		else
			return false;
	}

	bool InputManager::JoyButtonReleased(int button, int joynum) {

		if (joy[joynum] != NULL)
			return (mPrevJoyButtonState[joynum][button] != 0) && (mJoyButtonState[joynum][button] == 0);
		else
			return false;
	}

	bool InputManager::JoyHatDown(HAT_DIR direction, int joynum) {

		if (joy[joynum] != NULL)
			return ((mJoyHatState[joynum] & direction) != 0);
		else
			return false;
	}

	bool InputManager::JoyHatPressed(HAT_DIR direction, int joynum) {

		if (joy[joynum] != NULL)
			return ((mPrevJoyHatState[joynum] & direction) == 0) && ((mJoyHatState[joynum] & direction) != 0);
		else
			return false;
	}

	bool InputManager::JoyHatReleased(HAT_DIR direction, int joynum) {

		if (joy[joynum] != NULL)
			return ((mPrevJoyHatState[joynum] & direction) != 0) && ((mJoyHatState[joynum] & direction) == 0);
		else
			return false;
	}

	bool InputManager::JoyAxisDown(AXIS_NUM axis, AXIS_DIR direction, int joynum) {

		if (joy[joynum] != NULL) {
			if (direction < 0) {

				return (mJoyAxisState[joynum][axis] < direction);
			}
			else if (direction > 0) {

				return (mJoyAxisState[joynum][axis] > direction);
			}
			else
				return (mJoyAxisState[joynum][axis] > direction);
		}
		else
			return false;
	}

	bool InputManager::JoyAxisPressed(AXIS_NUM axis, AXIS_DIR direction, int joynum) {

		if (joy[joynum] != NULL) {
			if (direction < 0) {

				return ((mPrevJoyAxisState[joynum][axis] < direction) == 0) && ((mJoyAxisState[joynum][axis] < direction) != 0);
			}
			else if (direction > 0) {

				return ((mPrevJoyAxisState[joynum][axis] > direction) == 0) && ((mJoyAxisState[joynum][axis] > direction) != 0);
			}
			else
				return ((mPrevJoyAxisState[joynum][axis] > direction) == 0) && ((mJoyAxisState[joynum][axis] > direction) != 0);
		}
		else
			return false;
	}

	bool InputManager::JoyAxisReleased(AXIS_NUM axis, AXIS_DIR direction, int joynum) {

		if (joy[joynum] != NULL) {
			if (direction < 0) {

				return ((mPrevJoyAxisState[joynum][axis] < direction) != 0) && ((mJoyAxisState[joynum][axis] < direction) == 0);
			}
			else if (direction > 0) {

				return ((mPrevJoyAxisState[joynum][axis] > direction) != 0) && ((mJoyAxisState[joynum][axis] > direction) == 0);
			}
			else
				return ((mPrevJoyAxisState[joynum][axis] > direction) != 0) && ((mJoyAxisState[joynum][axis] > direction) == 0);
		}
		else
			return false;
	}

	int16_t InputManager::JoyAxis(AXIS_NUM axis, int joynum) {

		if (joy[joynum] != NULL)
			return mJoyAxisState[joynum][axis];
		else
			return 0x0000;
	}

	std::string InputManager::JoyStickName(int joynum) {

		std::string str = "No Controller";
		if (joy[joynum] != NULL) {
			str = SDL_JoystickName(joy[joynum]);
		}
		return str;
	}

	void InputManager::FindAttachedJoysticks() {

		for (int i = 0; i < MAX_JOYSTICKS; i++) {

			if (joy[i] != NULL) {

				SDL_JoystickClose(joy[i]);
				joy[i] = NULL;
			}
		}

		mNumJoysticks = SDL_NumJoysticks();

		for (int i = 0; i < mNumJoysticks; i++) {

			joy[i] = SDL_JoystickOpen(i);

			if (joy[i] != NULL) {

				mNumJoyButtons[i] = SDL_JoystickNumButtons(joy[i]);
				mNumJoyAxes[i] = SDL_JoystickNumAxes(joy[i]);

				mJoyButtonState[i] = new Uint8[mNumJoyButtons[i]];
				mPrevJoyButtonState[i] = new Uint8[mNumJoyButtons[i]];

				for (int b = 0; b < mNumJoyButtons[i]; b++) {
					mJoyButtonState[i][b] = SDL_JoystickGetButton(joy[i], b);
					mPrevJoyButtonState[i][b] = SDL_JoystickGetButton(joy[i], b);
				}

				//Assumes One Hat
				mJoyHatState[i] = SDL_JoystickGetHat(joy[i], 0);
				mPrevJoyHatState[i] = SDL_JoystickGetHat(joy[i], 0);

				mJoyAxisState[i] = new int16_t[mNumJoyAxes[i]];
				mPrevJoyAxisState[i] = new int16_t[mNumJoyAxes[i]];

				for (int a = 0; a < mNumJoyAxes[i]; a++) {
					mJoyAxisState[i][a] = SDL_JoystickGetAxis(joy[i], a);
					mPrevJoyAxisState[i][a] = SDL_JoystickGetAxis(joy[i], a);
				}
			}
		}
	}

	int InputManager::NumAttachedJoysticks() {

		return mNumJoysticks;
	}

	Vector2 InputManager::MousePos() {

		//Converting the mouse position into a Vector2 for ease of use since all entities use Vector2
		return Vector2((float)mMouseXPos, (float)mMouseYPos);
	}

	Vector2 InputManager::TouchPos() {
		return Vector2((float)mTouchXPos, (float)mTouchYPos);
	}

	bool InputManager::MouseButtonDown(MOUSE_BUTTON button) {

		//mask to be using for bit wise operations
		Uint32 mask = 0;

		switch (button) {

		case left:

			mask = SDL_BUTTON_LMASK;
			break;

		case right:

			mask = SDL_BUTTON_RMASK;
			break;

		case middle:

			mask = SDL_BUTTON_MMASK;
			break;

		case back:

			mask = SDL_BUTTON_X1MASK;
			break;

		case forward:

			mask = SDL_BUTTON_X2MASK;
			break;
		}

		//return true if the mask exists in the current mouse state
		return ((mMouseState & mask) != 0);
	}

	bool InputManager::MouseButtonPressed(MOUSE_BUTTON button) {

		//mask to be using for bit wise operations
		Uint32 mask = 0;

		switch (button) {

		case left:

			mask = SDL_BUTTON_LMASK;
			break;

		case right:

			mask = SDL_BUTTON_RMASK;
			break;

		case middle:

			mask = SDL_BUTTON_MMASK;
			break;

		case back:

			mask = SDL_BUTTON_X1MASK;
			break;

		case forward:

			mask = SDL_BUTTON_X2MASK;
			break;
		}

		//return true if the mask does not exist in the previous mouse state, but exists in the current one
		return ((mPrevMouseState & mask) == 0) && ((mMouseState & mask) != 0);
	}

	bool InputManager::MouseButtonReleased(MOUSE_BUTTON button) {

		Uint32 mask = 0;

		switch (button) {

		case left:

			mask = SDL_BUTTON_LMASK;
			break;

		case right:

			mask = SDL_BUTTON_RMASK;
			break;

		case middle:

			mask = SDL_BUTTON_MMASK;
			break;

		case back:

			mask = SDL_BUTTON_X1MASK;
			break;

		case forward:

			mask = SDL_BUTTON_X2MASK;
			break;
		}

		//return true if the mask exists in the previous mouse state, but does not exist in the current one
		return ((mPrevMouseState & mask) != 0) && ((mMouseState & mask) == 0);
	}

	void InputManager::Update() {

		//Updating the mouse state to get the key states of the current frame
		mMouseState = SDL_GetMouseState(&mMouseXPos, &mMouseYPos);

		SDL_Finger* touchState = SDL_GetTouchFinger(0, 0);
		if (touchState != NULL) {
			mTouchXPos = touchState->x;
			mTouchYPos = touchState->y;
		}

		for (int i = 0; i < MAX_JOYSTICKS; i++) {

			if (joy[i] != NULL) {

				mJoyButtonState[i] = new Uint8[mNumJoyButtons[i]];

				for (int b = 0; b < mNumJoyButtons[i]; b++) {
					mJoyButtonState[i][b] = SDL_JoystickGetButton(joy[i], b);
				}

				//Assumes One Hat
				mJoyHatState[i] = SDL_JoystickGetHat(joy[i], 0);

				mJoyAxisState[i] = new int16_t[mNumJoyAxes[i]];

				for (int a = 0; a < mNumJoyAxes[i]; a++) {
					mJoyAxisState[i][a] = SDL_JoystickGetAxis(joy[i], a);
				}
			}
		}
	}

	void InputManager::UpdatePrevInput() {

		//Copying the keyboard state into the previous keyboard state array at the end of the frame
		memcpy(mPrevKeyboardState, mKeyboardState, mKeyLength);
		//Setting the previous mouse state as the current mouse state at the end of the frame
		mPrevMouseState = mMouseState;

		for (int i = 0; i < MAX_JOYSTICKS; i++) {

			if (joy[i] != NULL) {

				mPrevJoyButtonState[i] = mJoyButtonState[i];
				mPrevJoyHatState[i] = mJoyHatState[i];
				mPrevJoyAxisState[i] = mJoyAxisState[i];
			}
		}
	}
}