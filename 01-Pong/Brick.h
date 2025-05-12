#pragma once

#include "GameObject.h"

using std::string;
using std::vector;
using std::map;

class Brick : public GameObject {
private:
    
protected:
public:

private:
public:
    Brick();
    Brick(Vector2 _pos, Vector2 _size, Color _color);
    virtual ~Brick();

    void Draw();
    void Update();

    void Collided();
};