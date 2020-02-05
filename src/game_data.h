#pragma once

#include <iostream>
#include <vector>


namespace GameData
{
#ifdef __APPLE__ //Retina display
	const int GAME_ZOOM = 8;
	const int WINDOW_WIDTH = 1472*2;
	const int WINDOW_HEIGHT = 1000*2;
#else
	const int GAME_ZOOM = 2;
	const int WINDOW_WIDTH = 1472;
	const int WINDOW_HEIGHT = 1000;
#endif
	const std::string GAME_TITLE = "GGJ 2020";
}

extern int countBads;
extern int countGoods;
