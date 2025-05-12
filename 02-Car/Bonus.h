#pragma once

#include "GameObject.h"

using std::string;
using std::vector;
using std::map;

class Bonus : public GameObject {
private:
    float speed{ 275 };

protected:
public:

private:
public:
    Bonus();
    Bonus(Vector2 _pos, Vector2 _size, Color _color);
    virtual ~Bonus();

    void Draw();
    void Update();
};