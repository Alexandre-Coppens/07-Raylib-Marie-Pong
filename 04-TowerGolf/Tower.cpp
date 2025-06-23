#include "Tower.h"
#include "GolfBall.h"
#include "Projectile.h"
#include <iostream>

using std::cout;
using std::to_string;

Tower::Tower(Vector2 _pos, Vector2 _size, TowerType _towerType) :
	Actor(_pos, _size, ActorType::Tower),
	towerType(TowerType(_towerType))
{
	sprite = TowerBible::GetTowerSkin(towerType);
}

Tower::~Tower(){
}

void Tower::Start(){
	towerStats = TowerBible::GetTowerStats(towerType);
}

void Tower::Update(Vector2* scroll){
	if (timer >= towerStats.timeBtwAttacks) {
		if (towerStats.autoAim) {
			vector<Actor*> hits = GetAllActorsInCollisionCirc(position, towerStats.range);
			for (auto i : hits) {
				if (GolfBall* ball = dynamic_cast<GolfBall*>(i)) {
					Attack();
					timer = 0;
					break;
				}
			}
		}
		else {
			Attack();
			timer = 0;
		}
	}
	else {
		timer += GetFrameTime();
	}
}

void Tower::Draw(Vector2* scroll) {
	if (mouseHover) {
		if (towerType == TowerType::PirateBoat || towerType == TowerType::Moai || towerType == TowerType::Volcano) {
			color.a = 50;
			DrawCircleV(Vector2Subtract(position, *scroll), TowerBible::GetTowerStats(towerType).range, color);
		}

		color.a = 255;
	}
	Actor::Draw(scroll);
	mouseHover = false;
}

void Tower::Attack() {
	switch (towerType)
	{
	case TowerType::Windmill:
		AttackWindmill();
		break;
	case TowerType::PirateBoat:
		AttackBoat();
		break;
	case TowerType::Dinosaur:
		AttackWindmill();
		break;
	case TowerType::Volcano:
		AttackVolcano();
		break;
	case TowerType::Moai:
		AttackMoai();
		break;
	}
	return;
}

void Tower::AttackWindmill() {
	Rectangle collider = Rectangle{ position.x + towerStats.squareDisplacement.x,
														position.y + towerStats.squareDisplacement.y,
														towerStats.squareSize, towerStats.squareSize };
	vector<Actor*> hits = GetAllActorsInCollisionRect(collider);


	for (auto i : hits) {
		if (GolfBall* ball = dynamic_cast<GolfBall*>(i)) {
			ball->ApplyDamage();
		}
		if (!towerStats.doesAttackPierce) break;
	}
}

void Tower::AttackBoat() {
	vector<Actor*> hits = GetAllActorsInCollisionCirc(position, towerStats.range);

	GolfBall* closest{};
	for (auto i : hits) {
		if (GolfBall* ball = dynamic_cast<GolfBall*>(i)) {
			if (closest != nullptr) {
				Vector2 distanceBest = closest->GetDistance();
				Vector2 distanceCurrent = ball->GetDistance();
				if (distanceCurrent.x <= distanceBest.x && distanceCurrent.y < distanceBest.y) closest = ball;
			}
			else closest = ball;
		}
	}
	if(closest != nullptr)	Actor::CreateActor("Projectile" + to_string(std::rand()), 0, new Projectile(position, Vector2{ 15,15 }, closest));
}

void Tower::AttackVolcano() {
	vector<Actor*> hits = GetAllActorsInCollisionCirc(position, towerStats.range);

	for (auto i : hits) {
		if (GolfBall* ball = dynamic_cast<GolfBall*>(i)) {
			ball->SetSlowed();
		}
	}
}

void Tower::AttackMoai() {
	vector<Actor*> hits = GetAllActorsInCollisionCirc(position, towerStats.range);

	for (auto i : hits) {
		if (GolfBall* ball = dynamic_cast<GolfBall*>(i)) {
			ball->ApplyDamage();
		}
	}
}



void Tower::MouseHover() { 
	mouseHover = true; 
}

void Tower::MouseInteract(Vector2* scroll){
}