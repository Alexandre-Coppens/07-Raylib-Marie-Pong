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

class Tower : public Actor {
private:
    TowerType towerType{};
    TowerStats towerStats{};

    uint8_t upgrade{ 0 };

    float timer{0};

    bool mouseHover;

public:

private:
public:
    Tower(Vector2 _pos, Vector2 _size, TowerType _towerType);
    ~Tower();

    void Start();
    void Update(Vector2* scroll);
    void Draw(Vector2* scroll);

    void Attack();
    void AttackWindmill();
    void AttackBoat();
    void AttackVolcano();
    void AttackMoai();

    void MouseInteract(Vector2* scroll);
    void MouseHover();
};