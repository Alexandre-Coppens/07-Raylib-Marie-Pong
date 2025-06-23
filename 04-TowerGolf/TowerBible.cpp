#include "TowerBible.h"

enum class TowerType;
struct TowerStats;

TowerBible::TowerBible(){
}

TowerBible::~TowerBible(){
}

int TowerBible::GetTowerPrice(const TowerType towerType)
{
	switch (towerType)
	{
	case TowerType::Windmill:
		return 30;
	case TowerType::PirateBoat:
		return 40;
	case TowerType::Dinosaur:
		return 40;
	case TowerType::Volcano:
		return 60;
	case TowerType::Moai:
		return 90;
	}
	return 30;
}

string TowerBible::GetTowerName(const TowerType towerType)
{
	switch (towerType)
	{
	case TowerType::Windmill:
		return "Windmill";
	case TowerType::PirateBoat:
		return "Pirate Boat";
	case TowerType::Dinosaur:
		return "Dinosaur";
	case TowerType::Volcano:
		return "Volcano";
	case TowerType::Moai:
		return "Moai";
	}
	return "Unknown";
}

string TowerBible::GetTowerPlacement(const TowerType towerType)
{
	switch (towerType)
	{
	case TowerType::Windmill:
		return "Attack Ball at regular interval\nPlaced on Path";
	case TowerType::PirateBoat:
		return "Auto Attack Balls in range\nPlaced on Water";
	case TowerType::Dinosaur:
		return "Attack multiple Balls at regular interval\nPlaced near Path";
	case TowerType::Volcano:
		return "Slow down Balls\nPlaced on Path";
	case TowerType::Moai:
		return "Attack Balls in Range\nPlaced near Path";
	}
	return "Unknown";
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

TowerStats TowerBible::GetTowerStats(const TowerType towerType)
{
	switch (towerType)
	{
	case TowerType::Windmill:
		return TowerStats{ 1, false, 0, 20, Vector2{-10, 20}, false };
	case TowerType::PirateBoat:
		return TowerStats{ 1, true, 150, 0, Vector2{0, 0}, false };
	case TowerType::Dinosaur:
		return TowerStats{ 1.5f, false, 0, 40, Vector2{-20, 50}, true };
	case TowerType::Volcano:
		return TowerStats{ 0.001f, true, 50, 0, Vector2{0, 0}, true };
	case TowerType::Moai:
		return TowerStats{ 2, true, 75, 0, Vector2{0, 0}, true };
	}
	return TowerStats{ 0.25f, false, 0, 20, Vector2{0, 20}, true };
}
