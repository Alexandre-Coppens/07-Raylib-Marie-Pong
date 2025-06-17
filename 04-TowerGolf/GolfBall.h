#pragma once

#include <string>
#include <vector>
#include <map>
#include "Raylib.h"
#include "GameObject.h"

using std::string;
using std::vector;
using std::map;

class GolfBall : public GameObject {
private:
    Vector2 startPos{};
    vector<Vector2> path{};
public:

private:
public:
    GolfBall();
    GolfBall(Vector2 _pos, Vector2 _size, Color color);
    ~GolfBall();

    void Start();
    void Update(Vector2* scroll);
    void Draw(Vector2* scroll);
};