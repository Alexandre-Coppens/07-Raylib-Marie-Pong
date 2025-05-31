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
    float rotation{ 0 };

    bool flipX{ false };
    Vector2 currentSprite{ 0,0 };

public:

private:
    void CarSide();

public:
    Car();
    Car(Vector2 _pos, Vector2 _size, Color color);
    ~Car();

    void Draw(Vector2* scroll);
    void Update(Vector2* scroll);
};