#pragma once

#include "GameObject.h"

using std::string;
using std::vector;
using std::map;

class Ball : public GameObject {
private:
    float speed{ 400 };
    Vector2 direction{ 0,0 };
    float soundPitch{ 1 };

protected:
public:
    int score{ 0 };

private:
public:
    Ball();
    Ball(Vector2 _pos, Vector2 _size, Color _color);
    virtual ~Ball();

    void Draw();
    void Update();
};