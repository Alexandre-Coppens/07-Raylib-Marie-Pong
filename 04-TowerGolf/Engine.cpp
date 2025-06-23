#include <iostream>
#include <algorithm>
#include "Terrain.h"
#include "Engine.h"
#include "DrawScreen.h"

#include "GolfBall.h"
#include "Player.h"
#include "UIBackground.h"
#include "GolfWaveSystem.h"

using std::cout;
using std::to_string;

Terrain terrain;

Engine::Engine() {
}

void Engine::Start(){
	assets = AssetList::GetInstance();
	terrain.tileSize = Vector2{ 45,45 };
	scroll = { -GetScreenWidth() * 0.5f - 30 ,-GetScreenHeight() * 0.5f - 40};
	Terrain::LoadMap("TowerPath");

//Create Objects Here
	Actor::CreateActor("Player", 0, new Player());
	Actor::CreateActor("UIBackground", 10, new UIBackground());
	Actor::CreateActor("GolfWaveSystem", 10, new GolfWaveSystem());

}

void Engine::Update() {

	vector<Actor*> goList = Actor::GetAllActors();
	for (int i = 0; i < goList.size(); i++) {
		if (goList[i]->needToDestroy) {
			Actor::RemoveActorFromLists(goList[i]);
		}
		else if (goList[i]->enabled) goList[i]->Update(&scroll);
	}

	bool notInBound = true;
}

void Engine::Draw() {
	BeginDrawing();
	ClearBackground(GREEN);
	DrawScreen(&scroll);
	EndDrawing();
}