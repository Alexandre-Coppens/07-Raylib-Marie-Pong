#pragma once

#include <string>
#include <vector>
#include <map>
#include "Raylib.h"
#include "GameObject.h"
#include "Terrain.h"

using std::string;
using std::vector;
using std::map;

class GolfBall : public GameObject {
private:
    Vector2 startPos{};
    Vector2 endPos{};
    vector<vector<Vector2>> path{};
    float timer;
    int cpath = 0;
public:

private:
public:
    GolfBall();
    GolfBall(Vector2 _pos, Vector2 _size, Color color);
    ~GolfBall();

    void Start();
    void Update(Vector2* scroll);
    void Draw(Vector2* scroll);

    void CreatePaths(vector<Terrain::Tile*> pathTiles, vector<Vector2> currentPath);
};