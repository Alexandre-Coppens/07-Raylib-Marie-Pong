#pragma once

#include <string>
#include <vector>
#include <map>
#include "Raylib.h"
#include "GameObject.h"

using std::string;
using std::vector;
using std::map;

class Cursor : public GameObject{
private:
public:

private:
public:
    Cursor();
    ~Cursor();

    void Draw();
    void Update();
};