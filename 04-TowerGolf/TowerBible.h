#pragma once

#include "Raylib.h"
#include "AssetsList.h"

enum class TowerType {
    Windmill,
    PirateBoat,
    Dinosaur,
    Volcano,
    Moai,
    None
};

class TowerBible{
public:

public:
	TowerBible();
	~TowerBible();

	static Texture2D* GetTowerSkin(const TowerType towerType);
};