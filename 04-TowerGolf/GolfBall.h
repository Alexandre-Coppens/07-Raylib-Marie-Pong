#pragma once

#include <string>
#include <vector>
#include <map>
#include "Raylib.h"
#include "Actor.h"
#include "GolfBible.h"

using std::string;
using std::vector;
using std::map;

class GolfBall : public Actor {
private:
    vector<Vector2> path{};
    int currentTile{1};
    bool slowed{ 0 };

    GolfType golfType;
    GolfBallsStats golfBallStats{};

public:

private:
public:
    GolfBall(Vector2 _pos, Vector2 _size, GolfType _golfType, Color color);
    ~GolfBall();

    void Start();
    void Update(Vector2* scroll);
    void Draw(Vector2* scroll);

    void ApplyDamage();
    Vector2  GetDistance();

    const inline void SetSlowed() { slowed = true; }
    const inline void  SetPath(vector<Vector2> _path, int _currentTile) { path = _path; currentTile = _currentTile; }
    
};