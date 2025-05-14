#include <iostream>
#include <algorithm>
#include "Engine.h"
#include "Car.h"


using std::cout;
using std::to_string;

Engine::Engine() {
}

void Engine::Start(){
	assets = AssetList::GetInstance();
	GameObject::CreateGameObject("Car", new Car(Vector2{ GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f }, Vector2{ 50,50 }, RED));
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