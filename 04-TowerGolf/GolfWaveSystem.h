#pragma once

#include <map>
#include <string>
#include <vector>
#include "Raylib.h"
#include "Actor.h"
#include "Terrain.h"
#include "GolfBible.h"

using std::string;
using std::vector;
using std::map;



class GolfWaveSystem : public Actor {
private:
    uint16_t ballsLeft;

    Vector2 startPos{};
    Vector2 endPos{};
    vector<vector<Vector2>> path{};

    bool canSpawnWave{ true };
    float timer{ 99 };
    int currentSpawnNbr{ 0 };
    int currentPart{ 0 };
    int currentWave{ 0 };

public:

private:
public:
    GolfWaveSystem();
    ~GolfWaveSystem();

    void Start();
    void Update(Vector2* scroll);
    void Draw(Vector2* scroll);

    void CreatePaths(vector<Terrain::Tile*> pathTiles, vector<Vector2> currentPath);
    void SpawnWave();
    void CreateGolfBall(GolfType golfType);
};