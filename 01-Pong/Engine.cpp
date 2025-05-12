#include <iostream>
#include <algorithm>
#include "Engine.h"

#include "Ball.h"
#include "Bonus.h"
#include "Paddle.h"
#include "Brick.h"

using std::cout;
using std::to_string;

Engine::Engine() {
}

void Engine::Start(){
	assets = AssetList::GetInstance();
	lives = 3;
	score = 0;
	end = false;
	GameObject::CreateGameObject("Ball", new Ball(Vector2{ GetScreenWidth()*0.5f, GetScreenHeight()*0.5f}, Vector2{20,20}, RED));
	GameObject::CreateGameObject("Paddle", new Paddle(Vector2{ (GetScreenWidth()*0.5f) - 5, 625}, Vector2{80,20}, BLUE));
	SpawnBricks();
}

void Engine::Update() {
	vector<GameObject*> goList = GameObject::GetAllGameObjects();
	short ballNbr = 0;
	short bricks = 0;
	for (GameObject* go : goList) {
		if (go->enabled) go->Update();
		if (Ball* b = dynamic_cast<Ball*>(go)) {
			ballNbr++;
			score += b->score;
			b->score = 0;
		}
		if (Bonus* bo = dynamic_cast<Bonus*>(go)) ballNbr++;
		if (Brick* br = dynamic_cast<Brick*>(go)) bricks++;
		if (go->needToDestroy) {
			delete go;
		}
	}
	if (ballNbr == 0) {
		if (lives > 0) {
			GameObject::CreateGameObject("Ball", new Ball(Vector2{ GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f }, Vector2{ 20,20 }, RED));
			lives--;
		}
		else if (end == false){
			end = true;
			if (score > highscore) highscore = score;
		}
	}
	if (bricks == 0) {
		if (brickSpawn.size() <= 14) {
			brickSpawn.push_back(vector<bool>(10, true));
			brickSpawn.push_back(vector<bool>(10, true));
			brickSpawn.push_back(vector<bool>(10, true));
		}
		vector<GameObject*> balls = GameObject::GetAllGameObjectsWith(GameObjectType::Ball);
		for (GameObject* b : balls) b->needToDestroy = true;
		GameObject::CreateGameObject("Ball", new Ball(Vector2{ GetScreenWidth() * 0.5f, GetScreenHeight() * 0.5f }, Vector2{ 20,20 }, RED));
		SpawnBricks();
	}

	if (IsKeyDown(KEY_R)) {
		GameObject::DestroyGameObjectList();
		Start();
	}
}

void Engine::Draw() {
	BeginDrawing();
	ClearBackground(RAYWHITE);
	vector<GameObject*> goList = GameObject::GetAllGameObjects();
	for (GameObject* go : goList) {
		if (go->enabled) go->Draw();
	}
	DrawTextEx(AssetList::textFont["Setback"], ("Lives " + to_string(lives)).c_str(), Vector2{10,0}, 20, 5, DARKGRAY);
	if (score >= highscore) 	DrawTextEx(AssetList::textFont["Setback"], (to_string(score)).c_str(), Vector2{ 300,0 }, 20, 5, ORANGE);
	else DrawTextEx(AssetList::textFont["Setback"], (to_string(score)).c_str(), Vector2{ 300,0 }, 20, 5, DARKGRAY);
	EndDrawing();

	if (end) {
		if (score >= highscore) 	DrawTextEx(AssetList::textFont["Setback"], ("Score " + to_string(score)).c_str(), Vector2{ 150,250 }, 20, 5, ORANGE);
		else DrawTextEx(AssetList::textFont["Setback"], ("Score " + to_string(score)).c_str(), Vector2{ 150,250 }, 20, 5, DARKGRAY);
		DrawTextEx(AssetList::textFont["Setback"], ("HighScore " + to_string(highscore)).c_str(), Vector2{ 150,280 }, 20, 5, DARKGRAY);
		DrawTextEx(AssetList::textFont["Setback"], "Press R to restart", Vector2{ 150,310 }, 20, 5, RED);
	}
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
		brickList[rand() % brickList.size()]->color = GREEN;
	}
}