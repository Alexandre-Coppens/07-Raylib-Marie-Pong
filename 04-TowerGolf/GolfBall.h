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
    vector<Vector2> path{};
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

    void ApplyDamage();
    Vector2  GetDistance();

    const inline void  SetPath(vector<Vector2> _path) { path = _path; }
    
};