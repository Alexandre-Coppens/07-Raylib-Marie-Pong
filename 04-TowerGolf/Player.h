#pragma once

#include <string>
#include <vector>
#include <map>
#include "Raylib.h"
#include "Actor.h"
#include "Terrain.h"

using std::string;
using std::vector;
using std::map;

class Player : public Actor {
private:
    Vector2 startPos{};
    Vector2 endPos{};
    vector<vector<Vector2>> path{};
    int currentPath{};
    int currentTile{ 1 };
    float speed = 50;

public:

private:
public:
    Player();
    ~Player();

    void Start();
    void Update(Vector2* scroll);
    void Draw(Vector2* scroll);
    
    void MouseInteract(Vector2* scroll);
};