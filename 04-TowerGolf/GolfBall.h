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

class GolfBall : public Actor {
private:
    Vector2 startPos{};
    Vector2 endPos{};
    vector<vector<Vector2>> path{};
    int currentPath{};
    int currentTile{1};
    float speed = 50;

public:

private:
public:
    GolfBall(Vector2 _pos, Vector2 _size, Color color);
    ~GolfBall();

    void Start();
    void Update(Vector2* scroll);
    void Draw(Vector2* scroll);

    void CreatePaths(vector<Terrain::Tile*> pathTiles, vector<Vector2> currentPath);
};