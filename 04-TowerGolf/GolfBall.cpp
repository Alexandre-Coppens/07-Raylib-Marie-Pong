#include <iostream>
#include <fstream>
#include "GolfBall.h"
#include "Terrain.h"

using std::ofstream;
using std::ifstream;

using std::to_string;
using std::cout;

GolfBall::GolfBall() {
}

GolfBall::GolfBall(Vector2 _pos, Vector2 _size, Color _color) {
	sprite = &AssetList::SpriteList["SpriteSheet_Car"];
	position = _pos;
	size = _size;
	color = _color;
	type = GameObjectType::GolfBall;
	CreateRect();
}

GolfBall::~GolfBall() {
}

void GolfBall::Start() {
	vector<Terrain::Tile*> startTile = Terrain::GetEveryTilesWithModifier("Start");
	startTile = Terrain::GetEveryTilesWithModifier("Checkpoint");
}

void GolfBall::Update(Vector2* scroll) {
}

void GolfBall::Draw(Vector2* scroll) {
	//DrawTexturePro(*sprite, source, dest, Vector2Zero(), 0, color);
}