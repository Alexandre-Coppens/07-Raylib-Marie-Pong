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
	lives = 3;
	GameObject::CreateGameObject("Ball", new Ball(Vector2{ GetScreenWidth()*0.5f, GetScreenHeight()*0.5f}, Vector2{20,20}, RED));
	GameObject::CreateGameObject("Paddle", new Paddle(Vector2{ (GetScreenWidth()*0.5f) - 5, 625}, Vector2{80,20}, BLUE));
	SpawnBricks();
}

void Engine::Update() {
	vector<GameObject*> goList = GameObject::GetAllGameObjects();
	short ballNbr = 0;
	for (GameObject* go : goList) {
		if (go->enabled) go->Update();
		if (Ball* b = dynamic_cast<Ball*>(go)) ballNbr++;
		if (go->needToDestroy) {
			delete go;
		}
	}
	if (ballNbr == 0) {
		if (lives > 0) {
			GameObject::CreateGameObject("Ball", new Ball(Vector2{ GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f }, Vector2{ 20,20 }, RED));
			lives--;
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
	DrawTextEx(AssetList::textFont["Mecha"], ("Lives " + to_string(lives)).c_str(), Vector2{10,0}, 20, 5, GRAY);
	EndDrawing();
}

void Engine::SpawnBricks(){
	for (int i = 0; i < brickSpawn.size(); i++) {
		for (int j = 0; j < brickSpawn[i].size(); j++) {
			if (brickSpawn[i][j] == 1) {
				GameObject::CreateGameObject("Brick" + to_string(i) + ":" + to_string(j), new Brick(Vector2{ 6.0f + (j * 58), 75.0f + (i * 22) }, Vector2{ 56,20 }, BLUE));
			}
		}
	}
	vector<GameObject*> brickList= GameObject::GetAllGameObjectsWith(GameObjectType::Brick);
	for (int i = 0; i < 10; i++) {
		brickList[rand() % brickList.size() - 1]->color = GREEN;
	}
}