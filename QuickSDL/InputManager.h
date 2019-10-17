//---------------------------------------------------------------------//
// InputManager.h                                                      //
// Singleton                                                           //
// Handles all Input related functionality for keyboard and mouse.     //
//(To be expanded later to handle touch and contoller input)           //
//---------------------------------------------------------------------//
#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H
//---------------------------------------------------------------------
#include <string>
#include <SDL.h>
//---------------------------------------------------------------------
#include "MathHelper.h"
#include "UserDefines.h"
//---------------------------------------------------------------------
// QuickSDL
//---------------------------------------------------------------------
namespace QuickSDL {
	//-----------------------------------------------------------------
	// InputManager
	//-----------------------------------------------------------------
	class InputManager {

	public:
		//------------------------------------------------------------------------------------
		// MOUSE_BUTTON enum to discribe left mouse button, right mouse button, .. and so on  
		//------------------------------------------------------------------------------------
		enum MOUSE_BUTTON { left = 0, right, middle, back, forward };
		enum HAT_DIR { hat_up = SDL_HAT_UP, hat_right = SDL_HAT_RIGHT, hat_down = SDL_HAT_DOWN, hat_left = SDL_HAT_LEFT };
		enum AXIS_NUM { left_joy_x = 0, left_joy_y = 1, left_trigger = 2, right_joy_x = 3, right_joy_y = 4, right_trigger = 5,
						left_wiiu_joy_x = 0, left_wiiu_joy_y = 1, right_wiiu_joy_x = 2, right_wiiu_joy_y = 3,
						wiimote_joy_x = 0, wiimote_joy_y = 1 };
		enum AXIS_DIR { axis_up = -16000, axis_down = 16000, axis_left = -16000, axis_right = 16000, trigger_down = 0 };

	private:
		//Needed to make InputManager a singleton class
		static InputManager* sInstance;

		//Holds the keyboard key state of the last frame (used to catch key press and key release events)
		Uint8* mPrevKeyboardState;
		//Holds the keyboard key state of the current frame
		const Uint8* mKeyboardState;
		//The number of keys in the mKeyboardState array (used to copy the current keyboard state into the previous keyboard state)
		int mKeyLength;

		//Holds the mouse button state of the last frame (used to catch mouse button press and release events)
		Uint32 mPrevMouseState;
		//Holds the mouse button state of the current frame
		Uint32 mMouseState;

		//Used to retrieve the current mouse position using SDL_GetMouseState
		int mMouseXPos;
		int mMouseYPos;

		int mTouchXPos;
		int mTouchYPos;

		SDL_Joystick* joy[MAX_JOYSTICKS];
		int mNumJoysticks;

		Uint8* mPrevJoyButtonState[MAX_JOYSTICKS];
		Uint8* mJoyButtonState[MAX_JOYSTICKS];
		int mNumJoyButtons[MAX_JOYSTICKS];

		Uint8 mPrevJoyHatState[MAX_JOYSTICKS];
		Uint8 mJoyHatState[MAX_JOYSTICKS];

		int16_t* mPrevJoyAxisState[MAX_JOYSTICKS];
		int16_t* mJoyAxisState[MAX_JOYSTICKS];
		int mNumJoyAxes[MAX_JOYSTICKS];

	public:
		//-----------------------------------------
		//Returns a pointer to the class instance  
		//-----------------------------------------
		static InputManager* Instance();
		//-----------------------------------------------------
		//Releases the class instance and sets it back to NULL 
		//-----------------------------------------------------
		static void Release();

		//---------------------------------------------------------------
		//Returns true as long as the key given in scanCode is held down 
		//---------------------------------------------------------------
		bool KeyDown(SDL_Scancode scanCode);
		//------------------------------------------------------------------------------
		//Returns true only on the frame that the key given in scanCode is pressed down 
		//------------------------------------------------------------------------------
		bool KeyPressed(SDL_Scancode scanCode);
		//--------------------------------------------------------------------------
		//Returns true only on the frame that the key given in scanCode is released 
		//--------------------------------------------------------------------------
		bool KeyReleased(SDL_Scancode scanCode);

		//------------------------------------------------------------
		//Returns true as long as the given mouse button is held down 
		//------------------------------------------------------------
		bool MouseButtonDown(MOUSE_BUTTON botton);
		//----------------------------------------------------------------------
		//Returns true only on the frame that the given mouse button is pressed 
		//----------------------------------------------------------------------
		bool MouseButtonPressed(MOUSE_BUTTON button);
		//-----------------------------------------------------------------------
		//Returns true only on the frame that the given mouse button is released 
		//-----------------------------------------------------------------------
		bool MouseButtonReleased(MOUSE_BUTTON button);

		//------------------------------------------------------------------
		//Returns a Vector2 containing the current mouse position on screen 
		//------------------------------------------------------------------
		Vector2 MousePos();
		Vector2 TouchPos();

		bool JoyButtonDown(int button, int joynum = 0);
		bool JoyButtonPressed(int button, int joynum = 0);
		bool JoyButtonReleased(int button, int joynum = 0);

		bool JoyHatDown(HAT_DIR direction, int joynum = 0);
		bool JoyHatPressed(HAT_DIR direction, int joynum = 0);
		bool JoyHatReleased(HAT_DIR direction, int joynum = 0);

		bool JoyAxisDown(AXIS_NUM axis, AXIS_DIR direction, int joynum = 0);
		bool JoyAxisPressed(AXIS_NUM axis, AXIS_DIR direction, int joynum = 0);
		bool JoyAxisReleased(AXIS_NUM axis, AXIS_DIR direction, int joynum = 0);

		int16_t JoyAxis(AXIS_NUM axis, int joynum = 0);

		std::string JoyStickName(int joynum = 0);

		void FindAttachedJoysticks();
		int NumAttachedJoysticks();

		//----------------------------------------------------------------------------------
		//Updates the Input States (should be called once per frame before any input check) 
		//----------------------------------------------------------------------------------
		void Update();
		//-------------------------------------------------------------------------------------------------
		//Sets the current frame's key states as the previous key states (to be called in the LateUpdate)  
		//No input checks should be made in the current frame after this function is called                
		//-------------------------------------------------------------------------------------------------
		void UpdatePrevInput();

	private:
		//-----------------------------------------------------------------------------------------
		//Contructor is private so that Instance() must be used to get an instance when needed  
		//-----------------------------------------------------------------------------------------
		InputManager();
		//------------------------------------------------------------------------------------
		//Destructor is private so that the instance can only be destroyed using Release()  
		//------------------------------------------------------------------------------------
		~InputManager();
	};
}
#endif