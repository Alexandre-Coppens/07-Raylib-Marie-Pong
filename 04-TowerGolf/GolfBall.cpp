#include <iostream>
#include <fstream>
#include "GolfBall.h"
#include "GolfBible.h"
#include "Player.h"
#include "Terrain.h"

using std::ofstream;
using std::ifstream;

using std::to_string;
using std::cout;

GolfBall::GolfBall(Vector2 _pos, Vector2 _size, Color _color):
	Actor(_pos, _size, ActorType::GolfBall, &AssetList::SpriteList["Unknown"], _color)
{
}

GolfBall::~GolfBall() {
}

void GolfBall::Start() {
}

void GolfBall::Update(Vector2* scroll) {
	Vector2 next = Vector2Add(Vector2Multiply(path[currentTile], Terrain::tileSize), Vector2Multiply(Terrain::tileSize, Vector2{ 0.5f, 0.5f }));
	position = Vector2MoveTowards(position, next, speed * GetFrameTime());
	if (Vector2Distance(position, next) < 0.1f) {
		if (currentTile == path.size() - 1) {
			Player::lives--;
			Destroy();
		}
		else currentTile++;
	}
}

void GolfBall::Draw(Vector2* scroll) {
	Actor::Draw(scroll);
}

void GolfBall::ApplyDamage() {
	Player::money++;
	PlaySound(AssetList::soundList["GolfBall_Hit2"]);
	Destroy();
}

Vector2 GolfBall::GetDistance()
{
	Vector2 next = Vector2Add(Vector2Multiply(path[currentTile], Terrain::tileSize), Vector2Multiply(Terrain::tileSize, Vector2{ 0.5f, 0.5f }));
	return Vector2{ (float)path.size() - currentTile, Vector2Distance(position, next) };
}
