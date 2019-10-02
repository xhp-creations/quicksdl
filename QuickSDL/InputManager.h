//---------------------------------------------------------------------//
// InputManager.h                                                      //
// Singleton                                                           //
// Handles all Input related functionality for keyboard and mouse.     //
//(To be expanded later to handle touch and contoller input)           //
//---------------------------------------------------------------------//
#ifndef _INPUTMANAGER_H
#define _INPUTMANAGER_H
//---------------------------------------------------------------------
#include <SDL.h>
//---------------------------------------------------------------------
#include "MathHelper.h"

#define WIIU_JOY_A        SDL_CONTROLLER_BUTTON_A
#define WIIU_JOY_B        SDL_CONTROLLER_BUTTON_B
#define WIIU_JOY_X        SDL_CONTROLLER_BUTTON_X
#define WIIU_JOY_Y        SDL_CONTROLLER_BUTTON_Y

#define WIIU_JOY_PLUS     SDL_CONTROLLER_BUTTON_RIGHTSHOULDER
#define WIIU_JOY_L        SDL_CONTROLLER_BUTTON_START
#define WIIU_JOY_R        SDL_CONTROLLER_BUTTON_LEFTSTICK
#define WIIU_JOY_ZL       SDL_CONTROLLER_BUTTON_RIGHTSTICK
#define WIIU_JOY_ZR       SDL_CONTROLLER_BUTTON_LEFTSHOULDER
#define WIIU_JOY_MINUS    SDL_CONTROLLER_BUTTON_DPAD_UP

#define WIIU_JOY_DPAD_UP       SDL_CONTROLLER_BUTTON_DPAD_LEFT
#define WIIU_JOY_DPAD_DOWN     SDL_CONTROLLER_BUTTON_MAX
#define WIIU_JOY_DPAD_LEFT     SDL_CONTROLLER_BUTTON_DPAD_DOWN
#define WIIU_JOY_DPAD_RIGHT    SDL_CONTROLLER_BUTTON_DPAD_RIGHT

#define WIIU_JOY_L_THUMB   SDL_CONTROLLER_BUTTON_BACK
#define WIIU_JOY_R_THUMB   SDL_CONTROLLER_BUTTON_GUIDE

#define WIIU_JOY_L_LEFT   (SDL_GameControllerButton)16
#define WIIU_JOY_L_UP     (SDL_GameControllerButton)17
#define WIIU_JOY_L_RIGHT  (SDL_GameControllerButton)18
#define WIIU_JOY_L_DOWN   (SDL_GameControllerButton)19

#define WIIU_JOY_R_LEFT   (SDL_GameControllerButton)20
#define WIIU_JOY_R_UP     (SDL_GameControllerButton)21
#define WIIU_JOY_R_RIGHT  (SDL_GameControllerButton)22
#define WIIU_JOY_R_DOWN   (SDL_GameControllerButton)23

#define XINPUT_A        SDL_CONTROLLER_BUTTON_A
#define XINPUT_B        SDL_CONTROLLER_BUTTON_B
#define XINPUT_X        SDL_CONTROLLER_BUTTON_X
#define XINPUT_Y        SDL_CONTROLLER_BUTTON_Y

#define XINPUT_START    SDL_CONTROLLER_BUTTON_LEFTSTICK
#define XINPUT_BACK	    SDL_CONTROLLER_BUTTON_START
#define XINPUT_LB       SDL_CONTROLLER_BUTTON_BACK
#define XINPUT_RB       SDL_CONTROLLER_BUTTON_GUIDE

#define XINPUT_L_THUMB   SDL_CONTROLLER_BUTTON_RIGHTSTICK
#define XINPUT_R_THUMB   SDL_CONTROLLER_BUTTON_LEFTSHOULDER

#define XINPUT_GUIDE    SDL_CONTROLLER_BUTTON_RIGHTSHOULDER

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
						left_wiiu_joy_x = 0, left_wiiu_joy_y = 1, right_wiiu_joy_x = 2, right_wiiu_joy_y = 3 };
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

		SDL_Joystick* joy;

		Uint8* mPrevJoyButtonState;
		Uint8* mJoyButtonState;
		int mNumJoyButtons;

		Uint8 mPrevJoyHatState;
		Uint8 mJoyHatState;

		int16_t* mPrevJoyAxisState;
		int16_t* mJoyAxisState;
		int mNumJoyAxes;

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

		bool JoyButtonDown(int button);
		bool JoyButtonPressed(int button);
		bool JoyButtonReleased(int button);

		bool JoyHatDown(HAT_DIR direction);
		bool JoyHatPressed(HAT_DIR direction);
		bool JoyHatReleased(HAT_DIR direction);

		bool JoyAxisDown(AXIS_NUM axis, AXIS_DIR direction);
		bool JoyAxisPressed(AXIS_NUM axis, AXIS_DIR direction);
		bool JoyAxisReleased(AXIS_NUM axis, AXIS_DIR direction);

		int16_t JoyAxis(AXIS_NUM axis);

		void FindAttachedJoysticks();

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