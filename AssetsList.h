#pragma once

#include <string>
#include <vector>
#include <map>
#include "Raylib.h"

using std::string;
using std::vector;
using std::map;

class AssetList {
private:
    static Texture2D textureTemp;

public:
    static Music music;
    static map<string, Font> textFont;
    static map<string, Texture2D> SpriteList;
    static AssetList* instance;

private:
    AssetList();
    ~AssetList();
    void LoadTexture2D(string name, string link);

public:
    static AssetList* GetInstance();
};