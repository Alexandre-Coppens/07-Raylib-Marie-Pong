#pragma once

#include "Raylib.h"
#include "AssetsList.h"

enum class GolfType {
    White,
    Red,
    Metal,
    Fire,
    Boss
};

struct WavePart {
    GolfType golfType;
    uint16_t numberOfEnemies;
    float timeBtwEnemies;
    float timeBeforeNextPart;
};

class GolfBible {
public:
    static GolfBible* instance;
    static vector<vector<WavePart>> waves;

public:
    GolfBible();
    ~GolfBible();

    static Texture2D* GetGolfBallSkin(const GolfType golfType);
    static GolfBible* GetInstance();
};