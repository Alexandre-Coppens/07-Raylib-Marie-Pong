#include "TowerBible.h"

enum class TowerType;

TowerBible::TowerBible(){
}

TowerBible::~TowerBible(){
}

Texture2D* TowerBible::GetTowerSkin(const TowerType towerType) {
	switch (towerType)
	{
	case TowerType::Windmill:
		return &AssetList::SpriteList["Tower_Windmill"];
	case TowerType::PirateBoat:
		return &AssetList::SpriteList["Tower_Pirate"];
	case TowerType::Dinosaur:
		return &AssetList::SpriteList["Tower_Dinosaur"];
	case TowerType::Volcano:
		return &AssetList::SpriteList["Tower_Volcano"];
	case TowerType::Moai:
		return &AssetList::SpriteList["Tower_Moai"];
	}
	return &AssetList::SpriteList["Unknown"];
}