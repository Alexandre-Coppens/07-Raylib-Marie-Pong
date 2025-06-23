#include <iostream>
#include <fstream>
#include "Player.h"

using std::ofstream;
using std::ifstream;

using std::to_string;
using std::cout;

int Player::currentTile;
int Player::currentPath;
int Player::money;
int Player::lives;

Player::Player() {
	sprite = &AssetList::SpriteList["Button"];
	currentTile = 1;
	money = 100;
	lives = 100;
}

Player::~Player() {
}

void Player::Start() {
}

void Player::Update(Vector2* scroll) {
	vector<Actor*> actors = GetAllActors();
	for (auto i : actors) {
		if (GetMouseX() >= i->position.x - i->size.x * 0.5f && GetMouseX() <= i->position.x + i->size.x * 0.5f && GetMouseY() >= i->position.y - i->size.y * 0.5f && GetMouseY() <= i->position.y + i->size.y * 0.5f) {
			i->MouseHoverUI();
		}
		if (GetMouseX() >= i->position.x - i->size.x * 0.5f -scroll->x && GetMouseX() <= i->position.x + i->size.x * 0.5f - scroll->x && GetMouseY() >= i->position.y - i->size.y * 0.5f - scroll->y && GetMouseY() <= i->position.y + i->size.y * 0.5f - scroll->y) {
			i->MouseHover();
		}
	}
	if (IsMouseButtonPressed(0)) MouseInteract(scroll);
}

void Player::Draw(Vector2* scroll) {
	Rectangle source{ 0, 0, sprite->width, sprite->height };
	Rectangle dest{ 120, 30, 80, 30 };
	DrawTexturePro(*sprite, source, dest, Vector2{ 0, 0 }, 0, color);
	DrawTextEx(AssetList::textFont["pixantiqua"], to_string(money).c_str(), Vector2{ 130, 35 }, 20, 5, YELLOW);
	
	dest = Rectangle{ 520, 30, 80, 30 };
	DrawTexturePro(*sprite, source, dest, Vector2{ 0, 0 }, 0, color);
	DrawTextEx(AssetList::textFont["pixantiqua"], to_string(lives).c_str(), Vector2{ 530, 35 }, 20, 5, RED);
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

void Player::RemoveLives(int damages){
	lives -= damages;
}
