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
	if (IsMouseButtonPressed(0)) MouseInteract(scroll);
}

void Player::Draw(Vector2* scroll) {
}

void Player::MouseInteract(Vector2* scroll) {
	short isOnPath = 0; //0 = no, 1 = near a path, 2 = on a path
	Vector2 pathPosition;
	Vector2 mPos{ (int)floor(( GetMouseX() + scroll->x) / Terrain::tileSize.x), (int)floor((GetMouseY() + scroll->y) / Terrain::tileSize.y) };
	vector<Terrain::Tile*> pathTiles = Terrain::GetEveryTilesWithModifier("Path");
	for (int i = 0; i < pathTiles.size(); i++) {
		pathPosition = pathTiles[i]->position;
		if (Vector2Equals(pathPosition, mPos)) {
			isOnPath = 2;
			break;
		}
		else if (Vector2Equals(pathPosition, Vector2Add(mPos, Vector2{ 0, 1 }))) {
			isOnPath = 1;
		}
		else if (Vector2Equals(pathPosition, Vector2Add(mPos, Vector2{ 0, -1 }))) {
			isOnPath = 1;
		}
		else if (Vector2Equals(pathPosition, Vector2Add(mPos, Vector2{ 1, 0 }))) {
			isOnPath = 1;
		}
		else if (Vector2Equals(pathPosition, Vector2Add(mPos, Vector2{ -1, 0 }))) {
			isOnPath = 1;
		}
	}
	if (isOnPath == 2) cout << "This is a Path Tile \n";
	else if (isOnPath == 1) cout << "This is a Tile near the Path\n";
	else cout << "This is Null\n";
}
