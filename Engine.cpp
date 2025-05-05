#include <iostream>
#include <algorithm>
#include "Engine.h"

#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"

using std::cout;
using std::to_string;

Engine::Engine() {
}

void Engine::Start(){
	assets = AssetList::GetInstance();
	GameObject::CreateGameObject("Ball", new Ball(Vector2{ GetScreenWidth()*0.5f, GetScreenHeight()*0.5f}, Vector2{20,20}, RED));
	GameObject::CreateGameObject("Paddle", new Paddle(Vector2{ (GetScreenWidth()*0.5f) - 5, 625}, Vector2{80,20}, BLUE));
	SpawnBricks();
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

void Engine::SpawnBricks(){
	for (int i = 0; i < brickSpawn.size(); i++) {
		for (int j = 0; j < brickSpawn[i].size(); j++) {
			if (brickSpawn[i][j] == 1) {
				GameObject::CreateGameObject("Brick" + to_string(i) + ":" + to_string(j), new Brick(Vector2{ 2.0f + (j * 42), 75.0f + (i * 17) }, Vector2{ 40,15 }, BLUE));
			}
		}
	}
}