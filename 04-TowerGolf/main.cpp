#include <iostream>
#include <string>
#include "Engine.h"

using std::string;
Engine engine;

int main()
{
    InitWindow(700, 650, "Golf Defense");
    SetTargetFPS(60);

    InitAudioDevice();

	engine.Start();

	srand(time(NULL));
    while (!WindowShouldClose()){
        UpdateMusicStream(AssetList::music);
		engine.Update();
		engine.Draw();
	}

    UnloadMusicStream(AssetList::music);
    CloseAudioDevice();
    CloseWindow();
}