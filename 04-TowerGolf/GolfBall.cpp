#include <iostream>
#include <fstream>
#include "GolfBall.h"

#include "Player.h"
#include "Terrain.h"

using std::ofstream;
using std::ifstream;

using std::to_string;
using std::cout;

GolfBall::GolfBall(Vector2 _pos, Vector2 _size, GolfType _golfType, Color _color):
	Actor(_pos, _size, ActorType::GolfBall, &AssetList::SpriteList["Unknown"], _color),
	golfType( _golfType)
{
}

GolfBall::~GolfBall() {
}

void GolfBall::Start() {
	golfBallStats = GolfBible::GetGolfBallStats(golfType);
}

void GolfBall::Update(Vector2* scroll) {
	Vector2 next = Vector2Add(Vector2Multiply(path[currentTile], Terrain::tileSize), Vector2Multiply(Terrain::tileSize, Vector2{ 0.5f, 0.5f }));
	position = Vector2MoveTowards(position, next, golfBallStats.speed * GetFrameTime() * (slowed?0.33f:1));
	if (Vector2Distance(position, next) < 0.1f) {
		if (currentTile == path.size() - 1) {
			Player::lives -= GolfBible::GetGolfBallDamages(golfType);
			Destroy();
		}
		else currentTile++;
	}
	slowed = false;
}

void GolfBall::Draw(Vector2* scroll) {
	Actor::Draw(scroll);
}

void GolfBall::ApplyDamage() {
	Player::money++;
	PlaySound(AssetList::soundList["GolfBall_Hit2"]);
	GolfBall* pGolfBall{};
	switch (golfType)
	{
	case (GolfType::White):
		Destroy();
		delete pGolfBall;
		return;
	case (GolfType::Red):
		for (int i = 0; i < golfBallStats.splitInto; i++) {
			pGolfBall = static_cast<GolfBall*>(Actor::CreateActor("GolfWhite" + to_string(std::rand()), 3, new GolfBall(position, Vector2{ 20,20 }, GolfType::White, WHITE)));
			pGolfBall->SetPath(path, currentTile);
		}
		pGolfBall = nullptr;
		delete pGolfBall;
		Destroy();
		return;
	case (GolfType::Metal):
		break;
	case (GolfType::Fire):
		break;
	case (GolfType::Boss):
		break;
	default:
		break;
	}
	delete pGolfBall;
}

Vector2 GolfBall::GetDistance()
{
	Vector2 next = Vector2Add(Vector2Multiply(path[currentTile], Terrain::tileSize), Vector2Multiply(Terrain::tileSize, Vector2{ 0.5f, 0.5f }));
	return Vector2{ (float)path.size() - currentTile, Vector2Distance(position, next) };
}
