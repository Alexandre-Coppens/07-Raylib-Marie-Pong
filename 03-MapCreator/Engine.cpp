#include <iostream>
#include <algorithm>
#include "Engine.h"
#include "Terrain.h"
#include "DrawScreen.h"


using std::cout;
using std::to_string;

Terrain terrain;
int currentTexture{ 0 };

Engine::Engine() {
}

void Engine::Start(){
	assets = AssetList::GetInstance();
	terrain.tileSize = Vector2{ 50,50 };
	scroll = { GetScreenWidth() * 0.5f ,GetScreenHeight() * 0.5f };
}

void Engine::Update() {

	vector<GameObject*> goList = GameObject::GetAllGameObjects();
	for (GameObject* go : goList) {
		if (go->enabled) go->Update();
		if (go->needToDestroy) {
			delete go;
		}
	}

	if (IsKeyDown(KEY_W)) scroll.y += scrollSpeed.y * GetFrameTime();
	if (IsKeyDown(KEY_S)) scroll.y -= scrollSpeed.y * GetFrameTime();
	if (IsKeyDown(KEY_A)) scroll.x += scrollSpeed.x * GetFrameTime();
	if (IsKeyDown(KEY_D)) scroll.x -= scrollSpeed.x * GetFrameTime();

	Vector2 mPos{ (int)floor((-scroll.x + GetMouseX()) / terrain.tileSize.x), (int)floor((-scroll.y + GetMouseY()) / terrain.tileSize.y) };
	if(IsMouseButtonPressed(0)) terrain.AddNewTile(mPos, AssetList::GetNameAtPosition(currentTexture));

	if (GetMouseWheelMove()>0) {
		if (currentTexture == 0)currentTexture = AssetList::SpriteList.size() - 1;
		else currentTexture--;
	}
	if (GetMouseWheelMove() < 0) {
		if (currentTexture == AssetList::SpriteList.size() - 1)currentTexture = 0;
		else currentTexture++;
	}
}

void Engine::Draw() {
	BeginDrawing();
	ClearBackground(RAYWHITE);
	
	DrawScreen(&scroll);
	
	DrawText(("X. " + to_string((scroll.x - GetMouseX()) / terrain.tileSize.x)).c_str(), 10, 10, 20, GRAY);
	DrawText(("Y. " + to_string((scroll.y - GetMouseY()) / terrain.tileSize.y)).c_str(), 10, 30, 20, GRAY);
	DrawText(("Current Sprite:  " + AssetList::GetNameAtPosition(currentTexture)).c_str(), 10, 50, 20, ORANGE);
	EndDrawing();
}