#pragma once

#include "Raylib.h"
#include "Actor.h"
#include "TowerBible.h"

class UITower : public Actor {
private:
    TowerType towerType;
    bool isHovered;

public:

private:
public:
    UITower(Vector2 _pos, Vector2 _size, TowerType _towerType);
    ~UITower();

    void Start();
    void Update(Vector2* scroll);
    void Draw(Vector2* scroll);

    void MouseHoverUI();
    void Clicked();
};