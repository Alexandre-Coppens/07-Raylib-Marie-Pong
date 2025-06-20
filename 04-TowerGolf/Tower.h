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
    TowerType towerType;
public:

private:
public:
    Tower(Vector2 _pos, Vector2 _size, TowerType _towerType);
    ~Tower();

    void Start();
    void Update(Vector2* scroll);
    //void Draw(Vector2* scroll);

    void MouseInteract(Vector2* scroll);
};