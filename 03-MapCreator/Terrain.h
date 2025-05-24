#pragma once

#include <string>
#include <vector>
#include <map>
#include "Raylib.h"
#include "GameObject.h"

using std::string;
using std::vector;
using std::map;

class Terrain {
private:
public:
    struct Tile {
        Vector2 position{};
        short layer{};
        int rotation{};
        int dictionaryTexture{};
    };
    struct MapSave {
        map<int, string> dictionary;
        vector<vector<Tile>> terrain;
    };

    static map<int, string> dictionary;
    static vector<vector<Tile>> terrain;
    static Vector2 tileSize;
    static Vector2 position;
    static short maxLayer;

private:
public:
    Terrain();
    ~Terrain();

    void Update();

    void AddNewTile(int layer, int rotation, Vector2 pos, string name);
    void RemoveTile();
    int CheckInDictionary(string n);
};