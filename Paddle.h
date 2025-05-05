#pragma once

#include "GameObject.h"

using std::string;
using std::vector;
using std::map;

class Paddle : public GameObject {
private:
    float speed{ 400 };

protected:
public:

private:
public:
    Paddle();
    Paddle(Vector2 _pos, Vector2 _size, Color _color);
    virtual ~Paddle();

    void Draw();
    void Update();
};