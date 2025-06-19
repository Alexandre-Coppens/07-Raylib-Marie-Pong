#pragma once

#include <string>
#include <vector>
#include <map>
#include "Raylib.h"
#include "GameObject.h"

using std::string;
using std::vector;
using std::map;

class UIBackground : public GameObject {
private:
public:

private:
public:
    UIBackground();
    UIBackground(Vector2 _pos, Vector2 _size, Color color);
    ~UIBackground();

    void Start();
    void Update(Vector2* scroll);
    void Draw(Vector2* scroll);
};