#include <iostream>
#include <algorithm>
#include "Terrain.h"
#include "Engine.h"
#include "DrawScreen.h"

#include "GolfBall.h"
#include "Player.h"
#include "UIBackground.h"

using std::cout;
using std::to_string;

Terrain terrain;

Engine::Engine() {
}

void Engine::Start(){
	assets = AssetList::GetInstance();
	terrain.tileSize = Vector2{ 50,50 };
	scroll = { -GetScreenWidth() * 0.5f ,-GetScreenHeight() * 0.5f };
	Terrain::LoadMap("TowerPath");

//Create Objects Here
	Actor::CreateActor("GolfBallTest", 3, new GolfBall(Vector2{ 0, 0 }, Vector2{ 20,20 }, RED));
	Actor::CreateActor("Player", 0, new Player());
	Actor::CreateActor("UIBackground", 10, new UIBackground());

	vector<Actor*> goList = Actor::GetAllActors();
	for (Actor* go : goList) {
		go->Start();
	}
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