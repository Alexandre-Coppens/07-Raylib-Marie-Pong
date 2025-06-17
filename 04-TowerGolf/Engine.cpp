#include <iostream>
#include <algorithm>
#include "Terrain.h"
#include "Engine.h"
#include "DrawScreen.h"
#include "GolfBall.h"

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
	GameObject::CreateGameObject("GolfBallTest", 10, new GolfBall(Vector2{ 0, 0 }, Vector2{ 50,50 }, RED));


	vector<GameObject*> goList = GameObject::GetAllGameObjects();
	for (GameObject* go : goList) {
		go->Start();
	}
}

void Engine::Update() {

	vector<GameObject*> goList = GameObject::GetAllGameObjects();
	for (GameObject* go : goList) {
		if (go->enabled) go->Update(&scroll);
		if (go->needToDestroy) {
			delete go;
		}
	}

	bool notInBound = true;
}

void Engine::Draw() {
	BeginDrawing();
	ClearBackground(GREEN);
	DrawScreen(&scroll);
	EndDrawing();
}