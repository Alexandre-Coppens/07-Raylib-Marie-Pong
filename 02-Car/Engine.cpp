#include <iostream>
#include <algorithm>
#include "Terrain.h"
#include "Engine.h"
#include "DrawScreen.h"
#include "Car.h"

using std::cout;
using std::to_string;

Terrain terrain;

Engine::Engine() {
}

void Engine::Start(){
	assets = AssetList::GetInstance();
	terrain.tileSize = Vector2{ 50,50 };
	scroll = { -GetScreenWidth() * 0.5f ,-GetScreenHeight() * 0.5f };
	Terrain::LoadMap("CarTerrain");

	vector<Terrain::Tile*> startTile = Terrain::GetEveryTilesWithModifier("Start");
	GameObject::CreateGameObject("Car", 10, new Car(Vector2{ startTile[0]->position.x * terrain.tileSize.x, startTile[0]->position.y * terrain.tileSize.y }, Vector2{50,50}, RED));
	startTile = Terrain::GetEveryTilesWithModifier("Checkpoint");
	int maxCheckpoint = 0;
	for (auto t : startTile) {
		cout << Terrain::BreakString(Terrain::dictionary[t->dictionaryTexture], '_')[1];
		int checkpoint = stoi(Terrain::BreakString(Terrain::dictionary[t->dictionaryTexture], '_')[1]);
		if (checkpoint > maxCheckpoint) maxCheckpoint = checkpoint;
	}
	static_cast<Car*>(GameObject::GetGameObjectWithName("Car"))->SetMaxCheckpoint(maxCheckpoint);
}

void Engine::Update() {
	/*if (IsKeyDown(KEY_W)) scroll.y += scrollSpeed.y * GetFrameTime();
	if (IsKeyDown(KEY_S)) scroll.y -= scrollSpeed.y * GetFrameTime();
	if (IsKeyDown(KEY_A)) scroll.x += scrollSpeed.x * GetFrameTime();
	if (IsKeyDown(KEY_D)) scroll.x -= scrollSpeed.x * GetFrameTime();*/

	vector<GameObject*> goList = GameObject::GetAllGameObjects();
	for (GameObject* go : goList) {
		if (go->enabled) go->Update(&scroll);
		if (go->needToDestroy) {
			delete go;
		}
	}

	GameObject* car = GameObject::GetGameObjectWithName("Car");
	bool notInBound = true;
	while (notInBound) {
		if ((car->position.x - scroll.x) / GetScreenWidth() > 0.6f) {
			scroll.x += scrollSpeed.x * GetFrameTime();
		}
		else if ((car->position.x - scroll.x) / GetScreenWidth() < 0.4f) {
			scroll.x -= scrollSpeed.x * GetFrameTime();
		}
		else if ((car->position.y - scroll.y) / GetScreenHeight() > 0.6f) {
			scroll.y += scrollSpeed.y * GetFrameTime();
		}
		else if ((car->position.y - scroll.y) / GetScreenHeight() < 0.4f) {
			scroll.y -= scrollSpeed.y * GetFrameTime();
		}
		else notInBound = false;
	}
}

void Engine::Draw() {
	BeginDrawing();
	ClearBackground(GREEN);
	DrawScreen(&scroll);
	GameObject* car = GameObject::GetGameObjectWithName("Car");
	//DrawText(("X: " + to_string(car->position.x) + "; Y: " + to_string(car->position.y )).c_str(), 10, 30, 20, ORANGE);
	//DrawText(("ScrollX: " + to_string(scroll.x) + "; ScrollY: " + to_string(scroll.y)).c_str(), 10, 50, 20, GRAY);
	EndDrawing();
}