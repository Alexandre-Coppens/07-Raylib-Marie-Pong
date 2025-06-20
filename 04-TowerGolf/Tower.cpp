#include "Tower.h"

Tower::Tower(Vector2 _pos, Vector2 _size, TowerType _towerType) :
	Actor(_pos, _size, ActorType::Tower),
	towerType(TowerType(_towerType))
{
	sprite = TowerBible::GetTowerSkin(towerType);
}

Tower::~Tower(){
}

void Tower::Start(){
}

void Tower::Update(Vector2* scroll){
}

void Tower::MouseInteract(Vector2* scroll){
}
