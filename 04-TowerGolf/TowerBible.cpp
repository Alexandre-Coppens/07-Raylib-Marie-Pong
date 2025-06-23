#include "TowerBible.h"

enum class TowerType;
struct TowerStats;

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

int TowerBible::GetTowerPrice(const TowerType towerType)
{
	switch (towerType)
	{
	case TowerType::Windmill:
		return 30;
	case TowerType::PirateBoat:
		return 30;
	case TowerType::Dinosaur:
		return 30;
	case TowerType::Volcano:
		return 30;
	case TowerType::Moai:
		return 30;
	}
	return 30;
}

TowerStats TowerBible::GetTowerStats(const TowerType towerType)
{
	switch (towerType)
	{
	case TowerType::Windmill:
		return TowerStats{ 1.25f, false, 0, 20, Vector2{0, 20}, false };
	case TowerType::PirateBoat:
		return TowerStats{ 0.25f, false, 0, 20, Vector2{0, 20}, true };
	case TowerType::Dinosaur:
		return TowerStats{ 0.25f, false, 0, 20, Vector2{0, 20}, true };
	case TowerType::Volcano:
		return TowerStats{ 0.25f, false, 0, 20, Vector2{0, 20}, true };
	case TowerType::Moai:
		return TowerStats{ 0.25f, false, 0, 20, Vector2{0, 20}, true };
	}
	return TowerStats{ 0.25f, false, 0, 20, Vector2{0, 20}, true };
}
