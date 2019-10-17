#ifndef _USERDEFINES_H
#define _USERDEFINES_H

//-------------------------------------------------------------------
// Define per project, PROJECT_TITLE must be a string
//-------------------------------------------------------------------
#define PROJECT_WIDTH		1280
#define PROJECT_HEIGHT		720
#define PROJECT_TITLE		"QuickSDL"  // Is not seen on Wii U

//-------------------------------------------------------------------
// Uncomment for projects larger than 1280 x 720 on the Wii U
//-------------------------------------------------------------------
//#define USE_SCALING
#ifdef USE_SCALING
//-------------------------------------------------------------------
// Set value to make screen size below or at 1280 x 720 on the Wii U
//-------------------------------------------------------------------
#define SCALE_RATIO			0.85f
#endif

//-------------------------------------------------------------------
// Controller defines
//-------------------------------------------------------------------
#ifndef __WIIU__
#define MAX_JOYSTICKS		4

#define XINPUT_A			SDL_CONTROLLER_BUTTON_A
#define XINPUT_B			SDL_CONTROLLER_BUTTON_B
#define XINPUT_X			SDL_CONTROLLER_BUTTON_X
#define XINPUT_Y			SDL_CONTROLLER_BUTTON_Y

#define XINPUT_START		SDL_CONTROLLER_BUTTON_LEFTSTICK
#define XINPUT_BACK			SDL_CONTROLLER_BUTTON_START
#define XINPUT_LB			SDL_CONTROLLER_BUTTON_BACK
#define XINPUT_RB			SDL_CONTROLLER_BUTTON_GUIDE

#define XINPUT_L_THUMB		SDL_CONTROLLER_BUTTON_RIGHTSTICK
#define XINPUT_R_THUMB		SDL_CONTROLLER_BUTTON_LEFTSHOULDER

#define XINPUT_GUIDE		SDL_CONTROLLER_BUTTON_RIGHTSHOULDER

#else
#define MAX_JOYSTICKS		5

#define WIIU_JOY_A			SDL_CONTROLLER_BUTTON_A
#define WIIU_JOY_B			SDL_CONTROLLER_BUTTON_B
#define WIIU_JOY_X			SDL_CONTROLLER_BUTTON_X
#define WIIU_JOY_Y			SDL_CONTROLLER_BUTTON_Y

#define WII_MOTE_A			WIIU_JOY_A
#define WII_MOTE_B			WIIU_JOY_B
#define WII_MOTE_C			WIIU_JOY_Y
#define WII_MOTE_Z			WIIU_JOY_X

#define WIIU_JOY_PLUS		SDL_CONTROLLER_BUTTON_RIGHTSHOULDER
#define WIIU_JOY_L			SDL_CONTROLLER_BUTTON_START
#define WIIU_JOY_R			SDL_CONTROLLER_BUTTON_LEFTSTICK
#define WIIU_JOY_ZL			SDL_CONTROLLER_BUTTON_RIGHTSTICK
#define WIIU_JOY_ZR			SDL_CONTROLLER_BUTTON_LEFTSHOULDER
#define WIIU_JOY_MINUS		SDL_CONTROLLER_BUTTON_DPAD_UP

#define WII_MOTE_1			WIIU_JOY_L
#define WII_MOTE_2			WIIU_JOY_R

#define WIIU_JOY_DPAD_UP			SDL_CONTROLLER_BUTTON_DPAD_LEFT
#define WIIU_JOY_DPAD_DOWN			SDL_CONTROLLER_BUTTON_MAX
#define WIIU_JOY_DPAD_LEFT			SDL_CONTROLLER_BUTTON_DPAD_DOWN
#define WIIU_JOY_DPAD_RIGHT			SDL_CONTROLLER_BUTTON_DPAD_RIGHT

#define WII_MOTE_L_SIDE_DPAD_UP			WIIU_JOY_DPAD_RIGHT
#define WII_MOTE_L_SIDE_DPAD_DOWN		WIIU_JOY_DPAD_LEFT
#define WII_MOTE_L_SIDE_DPAD_LEFT		WIIU_JOY_DPAD_UP
#define WII_MOTE_L_SIDE_DPAD_RIGHT		WIIU_JOY_DPAD_DOWN

#define WII_MOTE_R_SIDE_DPAD_UP			WIIU_JOY_DPAD_LEFT
#define WII_MOTE_R_SIDE_DPAD_DOWN		WIIU_JOY_DPAD_RIGHT
#define WII_MOTE_R_SIDE_DPAD_LEFT		WIIU_JOY_DPAD_DOWN
#define WII_MOTE_R_SIDE_DPAD_RIGHT		WIIU_JOY_DPAD_UP

#define WIIU_JOY_L_THUMB			SDL_CONTROLLER_BUTTON_BACK
#define WIIU_JOY_R_THUMB			SDL_CONTROLLER_BUTTON_GUIDE

#define WIIU_JOY_L_LEFT			(SDL_GameControllerButton)16
#define WIIU_JOY_L_UP			(SDL_GameControllerButton)17
#define WIIU_JOY_L_RIGHT		(SDL_GameControllerButton)18
#define WIIU_JOY_L_DOWN			(SDL_GameControllerButton)19

#define WIIU_JOY_R_LEFT			(SDL_GameControllerButton)20
#define WIIU_JOY_R_UP			(SDL_GameControllerButton)21
#define WIIU_JOY_R_RIGHT		(SDL_GameControllerButton)22
#define WIIU_JOY_R_DOWN			(SDL_GameControllerButton)23
#endif

#endif