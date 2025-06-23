#pragma once

#include <string>
#include <vector>
#include <map>
#include "Raylib.h"
#include "Actor.h"
#include "TowerBible.h"

using std::string;
using std::vector;
using std::map;

class UINewTower : public Actor {
private:
    TowerType towerType;
public:

private:
    void PlaceTower(Vector2* scroll);
    void CheckCanBePlaced(Vector2* scroll);
    short CheckTile(Vector2* scroll);

public:
    UINewTower(TowerType _towerType);
    ~UINewTower();

    void Start();
    void Update(Vector2* scroll);
    void Draw(Vector2* scroll);
};