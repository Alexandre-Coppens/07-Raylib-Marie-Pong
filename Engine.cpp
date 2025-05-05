#include <iostream>
#include <algorithm>
#include "Engine.h"

#include "Ball.h"
#include "Paddle.h"

using std::cout;
using std::to_string;

Engine::Engine() {
}

void Engine::Start(){
	assets = AssetList::GetInstance();
	GameObject::CreateGameObject("Ball", new Ball(Vector2{ GetScreenWidth()*0.5f, GetScreenHeight()*0.5f}, Vector2{10,10}, RED));
	GameObject::CreateGameObject("Paddle", new Paddle(Vector2{ (GetScreenWidth()*0.5f) - 5, 625}, Vector2{30,10}, BLUE));
}

void Engine::Update() {
	vector<GameObject*> goList = GameObject::GetAllGameObjects();
	for (GameObject* go : goList) {
		if (go->enabled) go->Update();
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
