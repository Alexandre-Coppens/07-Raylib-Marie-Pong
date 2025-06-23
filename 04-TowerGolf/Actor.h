#pragma once

#include <string>
#include <vector>
#include <map>
#include "Raylib.h"
#include "raymath.h"
#include "AssetsList.h"

using std::string;
using std::vector;
using std::map;

enum class ActorType {
    GolfBall,
    UI,
    UINewTower,
    Tower,
    None
};

class Actor {
private:
protected:
    static map<string, Actor*> ActorList;
    static vector<vector<Actor*>> ActorsByLayer;

public:
    bool enabled{ true };
    bool hasCollision{ true };
    bool needToDestroy{ false };

    string name{ "" };
    Vector2 position{ 0,0 };
    Vector2 size{ 0,0 };
    short layer{ 0 };
    Texture2D* sprite{};
    Color color{WHITE};
    ActorType type{ ActorType::None};

private:
protected:

public:
    Actor(Vector2 _pos = Vector2Zero(),
        Vector2 _size = Vector2Zero(),
        ActorType _type = ActorType::None,
        Texture2D* _sprite = &AssetList::SpriteList["Unknown"],
        Color _color = WHITE);
    virtual ~Actor();
    
    virtual void Start();
    virtual void Update(Vector2* scroll);
    virtual void Draw(Vector2* scroll);

    //Put the actor on the Destroy list for next Update
    void Destroy();
    static void RemoveActorFromLists(Actor* go);

    //Mouse Gestion
    virtual void Clicked();
    virtual void MouseHover();
    virtual void MouseHoverUI();

    //Collision Gestion
    virtual void Collided();

    static Actor* CreateActor(const string id, int layer, Actor* actor);

    static Actor* GetActorWithName(string _name);
    static vector<Actor*> GetAllActors();
    static vector<vector<Actor*>>* GetAllActorsLayered();
    static vector<Actor*> GetAllActorsWith(ActorType type);
    static vector<Actor*> GetAllActorsInCollisionRect(Rectangle collider);
    static vector<Actor*> GetAllActorsInCollisionCirc(Vector2 origin, float radius);

    static void DestroyActorList();
};