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

		delete[] mPrevJoyButtonState;
		mPrevJoyButtonState = NULL;

		mJoyButtonState = NULL;

		delete[] mPrevJoyAxisState;
		mPrevJoyAxisState = NULL;

		mJoyAxisState = NULL;
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

	bool InputManager::JoyButtonDown(int button) {

		if (joy != NULL)
			return (mJoyButtonState[button] != 0);
		else
			return false;
	}

	bool InputManager::JoyButtonPressed(int button) {

		if (joy != NULL)
			return (mPrevJoyButtonState[button]) == 0 && (mJoyButtonState[button] != 0);
		else
			return false;
	}

	bool InputManager::JoyButtonReleased(int button) {

		if (joy != NULL)
			return (mPrevJoyButtonState[button] != 0) && (mJoyButtonState[button] == 0);
		else
			return false;
	}

	bool InputManager::JoyHatDown(HAT_DIR direction) {

		if (joy != NULL)
			return ((mJoyHatState & direction) != 0);
		else
			return false;
	}

	bool InputManager::JoyHatPressed(HAT_DIR direction) {

		if (joy != NULL)
			return ((mPrevJoyHatState & direction) == 0) && ((mJoyHatState & direction) != 0);
		else
			return false;
	}

	bool InputManager::JoyHatReleased(HAT_DIR direction) {

		if (joy != NULL)
			return ((mPrevJoyHatState & direction) != 0) && ((mJoyHatState & direction) == 0);
		else
			return false;
	}

	bool InputManager::JoyAxisDown(AXIS_NUM axis, AXIS_DIR direction) {
		if (joy != NULL) {
			if (direction < 0) {

				return (mJoyAxisState[axis] < direction);
			}
			else if (direction > 0) {

				return (mJoyAxisState[axis] > direction);
			}
			else
				return (mJoyAxisState[axis] > direction);
		}
		else
			return false;
	}

	bool InputManager::JoyAxisPressed(AXIS_NUM axis, AXIS_DIR direction) {
		if (joy != NULL) {
			if (direction < 0) {

				return ((mPrevJoyAxisState[axis] < direction) == 0) && ((mJoyAxisState[axis] < direction) != 0);
			}
			else if (direction > 0) {

				return ((mPrevJoyAxisState[axis] > direction) == 0) && ((mJoyAxisState[axis] > direction) != 0);
			}
			else
				return ((mPrevJoyAxisState[axis] > direction) == 0) && ((mJoyAxisState[axis] > direction) != 0);
		}
		else
			return false;
	}

	bool InputManager::JoyAxisReleased(AXIS_NUM axis, AXIS_DIR direction) {
		if (joy != NULL) {
			if (direction < 0) {

				return ((mPrevJoyAxisState[axis] < direction) != 0) && ((mJoyAxisState[axis] < direction) == 0);
			}
			else if (direction > 0) {

				return ((mPrevJoyAxisState[axis] > direction) != 0) && ((mJoyAxisState[axis] > direction) == 0);
			}
			else
				return ((mPrevJoyAxisState[axis] > direction) != 0) && ((mJoyAxisState[axis] > direction) == 0);
		}
		else
			return false;
	}

	int16_t InputManager::JoyAxis(AXIS_NUM axis) {

		if (joy != NULL)
			return mJoyAxisState[axis];
		else
			return 0x0000;
	}

	void InputManager::FindAttachedJoysticks() {

		if (joy != NULL) {

			SDL_JoystickClose(joy);
			joy = NULL;
		}

		for (int i = 0; i < SDL_NumJoysticks(); i++) {

			joy = SDL_JoystickOpen(i);
			if (joy != NULL)
				break;
		}

		mNumJoyButtons = SDL_JoystickNumButtons(joy);
		mNumJoyAxes = SDL_JoystickNumAxes(joy);

		if (joy != NULL) {

			mJoyButtonState = new Uint8[mNumJoyButtons];
			mPrevJoyButtonState = new Uint8[mNumJoyButtons];

			for (int b = 0; b < mNumJoyButtons; b++) {
				mJoyButtonState[b] = SDL_JoystickGetButton(joy, b);
				mPrevJoyButtonState[b] = SDL_JoystickGetButton(joy, b);
			}

			//Assumes One Hat
			mJoyHatState = SDL_JoystickGetHat(joy, 0);
			mPrevJoyHatState = SDL_JoystickGetHat(joy, 0);

			mJoyAxisState = new int16_t[mNumJoyAxes];
			mPrevJoyAxisState = new int16_t[mNumJoyAxes];

			for (int a = 0; a < mNumJoyAxes; a++) {
				mJoyAxisState[a] = SDL_JoystickGetAxis(joy, a);
				mPrevJoyAxisState[a] = SDL_JoystickGetAxis(joy, a);
			}
		}
	}

	Vector2 InputManager::MousePos() {

		//Converting the mouse position into a Vector2 for ease of use since all entities use Vector2
		return Vector2((float)mMouseXPos, (float)mMouseYPos);
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


		if (joy != NULL) {

			mJoyButtonState = new Uint8[mNumJoyButtons];

			for (int b = 0; b < mNumJoyButtons; b++) {
				mJoyButtonState[b] = SDL_JoystickGetButton(joy, b);
			}

			//Assumes One Hat
			mJoyHatState = SDL_JoystickGetHat(joy, 0);

			mJoyAxisState = new int16_t[mNumJoyAxes];

			for (int a = 0; a < mNumJoyAxes; a++) {
				mJoyAxisState[a] = SDL_JoystickGetAxis(joy, a);
			}
		}
	}

	void InputManager::UpdatePrevInput() {

		//Copying the keyboard state into the previous keyboard state array at the end of the frame
		memcpy(mPrevKeyboardState, mKeyboardState, mKeyLength);
		//Setting the previous mouse state as the current mouse state at the end of the frame
		mPrevMouseState = mMouseState;

		if (joy != NULL) {

			mPrevJoyButtonState = mJoyButtonState;
			mPrevJoyHatState = mJoyHatState;
			mPrevJoyAxisState = mJoyAxisState;
		}
	}
}