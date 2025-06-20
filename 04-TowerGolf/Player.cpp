#include <iostream>
#include <fstream>
#include "Player.h"

using std::ofstream;
using std::ifstream;

using std::to_string;
using std::cout;

Player::Player() {
}

Player::~Player() {
}

void Player::Start() {
}

void Player::Update(Vector2* scroll) {
	if (IsMouseButtonPressed(0)) MouseInteract(scroll);
}

void Player::Draw(Vector2* scroll) {
}

void Player::MouseInteract(Vector2* scroll) {
	cout << GetMouseX() << " : " << GetMouseY() << "\n";
	vector<Actor*> UiGoList = Actor::GetAllActorsWith(ActorType::UI);
	for (Actor* actor : UiGoList) {
		if (GetMouseX() >= actor->position.x - actor->size.x * 0.5f && GetMouseX() <= actor->position.x + actor->size.x * 0.5f && GetMouseY() >= actor->position.y - actor->size.y * 0.5f && GetMouseY() <= actor->position.y + actor->size.y *0.5f) {
			actor->Clicked();
		}
	}
}
