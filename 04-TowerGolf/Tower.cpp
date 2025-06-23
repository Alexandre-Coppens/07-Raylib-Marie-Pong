#include "Tower.h"
#include "GolfBall.h"
#include <iostream>

using std::cout;

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
	Actor::Draw(scroll);
	Rectangle collider = Rectangle{ position.x + towerStats.squareDisplacement.x - scroll->x,
														position.y + towerStats.squareDisplacement.y - scroll->y,
														towerStats.squareSize, towerStats.squareSize };
	DrawRectangleRec(collider, RED);
}

void Tower::Attack() {
	Rectangle collider = Rectangle{ position.x + towerStats.squareDisplacement.x,
														position.y + towerStats.squareDisplacement.y,
														towerStats.squareSize, towerStats.squareSize };
	vector<Actor*> hits = GetAllActorsInCollision(collider);

	
	for (auto i : hits) {
		if (dynamic_cast<GolfBall*>(i) != nullptr) {
			i->Destroy();
		}
		if (!towerStats.doesAttackPierce) break;
	}
}

void Tower::MouseInteract(Vector2* scroll){
}
