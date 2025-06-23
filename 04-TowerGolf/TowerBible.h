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

struct TowerStats {
    float timeBtwAttacks{0};
    bool autoAim{false};
    //For the towers who auto-aim
    float range{0};
    //For the towers with fixed collisions
    float squareSize{0};
    //Displacement of the square from center of Actor / Will rotate with Actor
    Vector2 squareDisplacement{ Vector2{0,0} };
    bool doesAttackPierce{false};
};

class TowerBible{
public:

public:
	TowerBible();
	~TowerBible();

	static Texture2D* GetTowerSkin(const TowerType towerType);
	static int GetTowerPrice(const TowerType towerType);
	static TowerStats GetTowerStats(const TowerType towerType);
};