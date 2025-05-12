#include <iostream>
#include <algorithm>
#include "Engine.h"
#include "GameObject.h"

using std::cout;
using std::to_string;

Engine::Engine() {
}

void Engine::Start(){
	assets = AssetList::GetInstance();
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
	ClearBackground(RAYWHITE);
	vector<GameObject*> goList = GameObject::GetAllGameObjects();
	for (GameObject* go : goList) {
		if (go->enabled) go->Draw();
	}
	EndDrawing();
}