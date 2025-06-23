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
    static Vector2 startPos;
    static Vector2 endPos;
    static vector<vector<Vector2>> path;
    static int currentPath;
    static int currentTile;

public:
    static int money;
    static int lives;

private:
public:
    Player();
    ~Player();

    void Start();
    void Update(Vector2* scroll);
    void Draw(Vector2* scroll);
    
    void MouseInteract(Vector2* scroll);
    static void RemoveLives(int damages);
};