#include "GameManager.h"
#ifdef __WIIU__
#include <romfs-wiiu.h>
#endif

int main(int argc, char* argv[]) {

#ifdef __WIIU__
	romfsInit();
#endif

	QuickSDL::GameManager* game = QuickSDL::GameManager::Instance();

	game->Run();

	QuickSDL::GameManager::Release();
	game = NULL;

#ifdef __WIIU__
	romfsExit();
#endif

	return 0;
}