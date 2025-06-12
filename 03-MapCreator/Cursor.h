#pragma once

#include <string>
#include <vector>
#include <map>
#include "Raylib.h"
#include "Actor.h"

using std::string;
using std::vector;
using std::map;

class Cursor : public Actor{
private:
public:

private:
public:
    Cursor();
    ~Cursor();

    void Draw();
    void Update();
};