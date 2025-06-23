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

struct GolfBallsStats {
    float speed{ 0 };
    float life{ 1 };
    float splitInto{ 0 };
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
    static int GetGolfBallDamages(const GolfType golfType);
    static GolfBallsStats GetGolfBallStats(const GolfType golfType);
    static GolfBible* GetInstance();

    WavePart MakeWavePart(GolfType golfType, uint16_t numberOfEnemies, float timeBtwEnemies, float timeBfNextPart);
};