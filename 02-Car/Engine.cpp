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
	GameObject::CreateGameObject("Car",  0, new Car(Vector2{ 0, 0 }, Vector2{ 50,50 }, RED));
	terrain.tileSize = Vector2{ 50,50 };
	scroll = { GetScreenWidth() * 0.5f ,GetScreenHeight() * 0.5f };
	Terrain::LoadMap("CarTerrain");
}

void Engine::Update() {
	vector<GameObject*> goList = GameObject::GetAllGameObjects();
	for (GameObject* go : goList) {
		if (go->enabled) go->Update();
		if (go->needToDestroy) {
			delete go;
		}
	}
}

void Engine::Draw() {
	BeginDrawing();
	ClearBackground(GREEN);
	DrawScreen(&scroll);
	EndDrawing();
}