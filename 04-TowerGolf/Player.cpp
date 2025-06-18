#include <iostream>
#include <fstream>
#include "Player.h"

using std::ofstream;
using std::ifstream;

using std::to_string;
using std::cout;

Player::Player() {
}

Player::Player(Vector2 _pos, Vector2 _size, Color _color) {
	sprite = &AssetList::SpriteList["Unknown"];
	position = _pos;
	size = _size;
	color = _color;
	type = GameObjectType::GolfBall;
	CreateRect();
}

Player::~Player() {
}

void Player::Start() {
}

void Player::Update(Vector2* scroll) {
}

void Player::Draw(Vector2* scroll) {
}
