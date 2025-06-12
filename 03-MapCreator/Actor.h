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

enum class GameObjectType {
    Car,
    Wall,
    Background,
    None
};

class Actor {
private:
protected:
    static map<string, Actor*> ActorList;
    static vector<vector<Actor*>> GameObjectsByLayer;
    Rectangle rect;
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
    GameObjectType type{ GameObjectType::None};

private:
protected:
    void CreateRect();

public:
    Actor();
    Actor(bool _enabled, string _name, Vector2 _pos, Vector2 _size, Texture2D* _sprite, GameObjectType _type);
    virtual ~Actor();
    
    virtual void Update();
    virtual void Draw(Vector2 scroll);
    //Put the object on the Destroy list for next Update
    void Destroy(); 

    //Mouse Gestion
    bool IsCursorInBounds();
    virtual int Clicked();

    //Collision Gestion
    virtual void Collided();

    static void CreateGameObject(const string id, Actor* gO);

    static Actor* GetGameObjectWithName(string _name);
    static vector<Actor*> GetAllGameObjects();
    static vector<vector<Actor*>>* GetAllGameObjectsLayered();
    static vector<Actor*> GetAllGameObjectsWith(GameObjectType type);
    
    static void DestroyGameObjectList();
};