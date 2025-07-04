#pragma once

#include <string>
#include <vector>
#include <map>
#include "Raylib.h"
#include "GameObject.h"

using std::string;
using std::vector;
using std::map;

class Car : public GameObject{
private:
    float thrust{ 10 };
    float decay{ 5 };
    float speed{ 0 };
    Vector2 deltaSpeed{ 0,0 };
    float towardSpeed{ 0 };
    Vector2 maxSpeed{ 200, -75 };
    bool isAccelerating = false;

    float turnRate{ 1 };
    float minTurnSpeed{ 50 };
    float rotation{ 7.85f };

    bool flipX{ false };
    Vector2 currentSprite{ 0,0 };

    int maxCheckpoint{ 0 };
    int currentCheckpoint{ 0 };

    float currentTimer{ 0 };
    float bestTimer{ 99999 };

public:

private:
    void CarSide();

    void SaveScore();
    void LoadScore();

public:
    Car();
    Car(Vector2 _pos, Vector2 _size, Color color);
    ~Car();

    void Draw(Vector2* scroll);
    void Update(Vector2* scroll);

    void SetMaxCheckpoint(int n){ maxCheckpoint = n; }
};