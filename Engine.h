#pragma once

#include <string>
#include <vector>
#include "AssetsList.h"

using std::string;
using std::vector;

class Engine {
private:
	AssetList* assets{};
    vector<vector<bool>> brickSpawn = {
        {1,1,0,0,1,1,1,1,1,1,0,0,1,1},
        {0,1,1,1,1,1,1,1,1,1,1,1,1,0},
        {0,1,1,1,1,0,0,0,0,1,1,1,1,0},
        {1,1,1,0,0,0,1,1,0,0,0,1,1,1},
        {1,1,0,1,0,1,1,1,1,0,1,0,1,1},
        {1,1,0,1,0,1,1,1,1,0,1,0,1,1},
        {1,1,1,0,0,0,1,1,0,0,0,1,1,1},
        {0,1,1,1,1,0,0,0,0,1,1,1,1,0},
        {0,1,1,1,1,1,1,1,1,1,1,1,1,0},
        {1,1,0,0,1,1,1,1,1,1,0,0,1,1},
    };
    int lives{};

private:
    void SpawnBricks();

public:
	Engine();
	void Start();
	void Update();
	void Draw();
};
