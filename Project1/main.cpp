#include "Game.h"
#include <Windows.h>

int main()
{
	//char path[MAX_PATH];
	//GetCurrentDirectoryA(MAX_PATH, path);
	//MessageBoxA(NULL, path, "Current Directory", MB_OK);
	Game game;
	game.Run();

	return 0;
}