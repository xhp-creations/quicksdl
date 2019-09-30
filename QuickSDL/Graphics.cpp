//---------------------------------------------------------------------//
// Graphics.cpp                                                        //
// Singleton                                                           //
// Handles the initialization of the graphics related SDL libraries    //
// and their release                                                   //
// Also handles texture and text loading                               //
//---------------------------------------------------------------------//
#include "Graphics.h"
//-------------------------------------------------------------
// QuickSDL
//-------------------------------------------------------------
namespace QuickSDL {

	//Initializing to NULL
	Graphics* Graphics::sInstance = NULL;
	//Initializing to false
	bool Graphics::sInitialized = false;

	Graphics* Graphics::Instance() {

		//Create a new instance if no instance was created before
		if (sInstance == NULL)
			sInstance = new Graphics();

		return sInstance;
	}

	void Graphics::Release() {

		delete sInstance;
		sInstance = NULL;

		sInitialized = false;
	}

	bool Graphics::Initialized() {

		return sInitialized;
	}

	Graphics::Graphics() {

		sInitialized = Init();
	}

	Graphics::~Graphics() {

		SDL_DestroyWindow(mWindow);
		mWindow = NULL;

		SDL_DestroyRenderer(mRenderer);
		mRenderer = NULL;

		//Closing all open SDL graphic libraries
		TTF_Quit();
		IMG_Quit();
		SDL_Quit();
	}

	bool Graphics::Init() {

		//Initialize SDL Video and Audio and handling initialization errors
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {

			printf("SDL Initialization Error: %s\n", SDL_GetError());
			return false;
		}

		//Creating the window
#ifndef USE_SCALING
		mWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
#else
		mWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH * SCALE_RATIO, SCREEN_HEIGHT * SCALE_RATIO, SDL_WINDOW_SHOWN);
#endif

		//Handling with window creation errors
		if (mWindow == NULL) {

			printf("Window Creation Error: %s\n", SDL_GetError());
			return false;
		}

		//Creating the renderer
#ifndef USE_SCALING
		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
#else
		mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
		SDL_RenderSetLogicalSize(mRenderer, SCREEN_WIDTH, SCREEN_HEIGHT);
#endif

		//Handling with the renderer creation errors
		if (mRenderer == NULL) {

			printf("Renderer Creation Error: %s\n", SDL_GetError());
			return false;
		}

		//Setting the renderer's clear color to black
		SDL_SetRenderDrawColor(mRenderer, mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a);

		//Initializing the SDL_image library and handling initialization errors
		int flags = IMG_INIT_PNG;
		if (!(IMG_Init(flags) & flags)) {

			printf("IMG Initialization Error: %s\n", IMG_GetError());
			return false;
		}

		//Initializing the SDL_ttf library and handling initialization errors
		if (TTF_Init() == -1) {

			printf("TTF Initialization Error: %s\n", TTF_GetError());
			return false;
		}

		//return true if no errors occurred during initialization
		return true;
	}

	SDL_Texture* Graphics::LoadTexture(std::string path) {

		SDL_Texture* tex = NULL;

		//load the image onto a surface
		SDL_Surface* surface = IMG_Load(path.c_str());
		//Handling image loading errors
		if (surface == NULL) {

			printf("Image Load Error: Path(%s) - Error(%s)\n", path.c_str(), IMG_GetError());
			return tex;
		}

		//Converting the surface into a texture to be able to render it using the renderer
		tex = SDL_CreateTextureFromSurface(mRenderer, surface);
		//Handling texture creation errors
		if (tex == NULL) {

			printf("Create Texture Error: %s\n", SDL_GetError());
			return tex;
		}

		//free the surface since only the texture is needed
		SDL_FreeSurface(surface);

		return tex;
	}

	SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color) {

		//Render the text onto a surface using the provided font and color
		SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
		//Handling font rendering errors
		if (surface == NULL) {

			printf("Text Render Error: %s\n", TTF_GetError());
			return NULL;
		}

		//Converting the surface into a texture to be able to render it using the renderer
		SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surface);
		//Handle texture creation errors
		if (tex == NULL) {

			printf("Text Texture Creation Error: %s\n", SDL_GetError());
			return NULL;
		}

		//free the surface since only the texture is needed
		SDL_FreeSurface(surface);

		return tex;
	}

	void Graphics::ClearBackBuffer() {

		SDL_SetRenderDrawColor(mRenderer, mClearColor.r, mClearColor.g, mClearColor.b, mClearColor.a);
		SDL_RenderClear(mRenderer);
		SDL_SetRenderDrawColor(mRenderer, mDrawColor.r, mDrawColor.g, mDrawColor.b, mDrawColor.a);
	}

	void Graphics::SetClearColor(SDL_Color color) {

		mClearColor = color;
	}

	void Graphics::SetDrawColor(SDL_Color color) {

		mDrawColor = color;
	}

	void Graphics::SetDrawColorAlpha(Uint8 alpha) {

		mDrawColor.a = alpha;
	}

	void Graphics::DrawTexture(SDL_Texture* tex, SDL_Rect* clip, SDL_Rect* rend, float angle, SDL_RendererFlip flip) {

		SDL_RenderCopyEx(mRenderer, tex, clip, rend, angle, NULL, flip);
	}

	void Graphics::DrawPoint(float x, float y) {

		SDL_RenderDrawPoint(mRenderer, x, y);
	}

	void Graphics::DrawLine(float startX, float startY, float endX, float endY) {

#if defined(USE_SCALING) && defined(__WIIU__)
		DrawLineWiiU(startX, startY, endX, endY);
#else
		SDL_RenderDrawLine(mRenderer, startX, startY, endX, endY);
#endif
	}

	void Graphics::DrawLineWiiU(float x1, float y1, float x2, float y2)
	{
		int s, dx, dy, m = 0;
		float xi, yi, x, y;
		dx = x2 - x1;
		dy = y2 - y1;
		if (abs(dx) > abs(dy)) {
			s = dx;
		}
		else {
			s = dy;
		}
		xi = dx / (float)s;
		yi = dy / (float)s;
		x = x1;
		y = y1;

		SDL_RenderDrawPoint(mRenderer, x1, y1);
		if (s > m) {

			for (m = 0; m < s; m++) {
				x += xi;
				y += yi;
				SDL_RenderDrawPoint(mRenderer, x, y);
			}
		}
		else {

			for (m = 0; m > s; m--) {
				x -= xi;
				y -= yi;
				SDL_RenderDrawPoint(mRenderer, x, y);
			}
		}
	}

	void Graphics::Render() {

		SDL_RenderPresent(mRenderer);
	}
}