#pragma once

#include "Raylib.h"
#include "Actor.h"

class Projectile : public Actor {
private:
    float speed{ 10 };
    Actor* target{};

public:

private:
public:
    Projectile(Vector2 _pos, Vector2 _size, Actor* target);
    ~Projectile();

    void Start();
    void Update(Vector2* scroll);
    void Draw(Vector2* scroll);
};