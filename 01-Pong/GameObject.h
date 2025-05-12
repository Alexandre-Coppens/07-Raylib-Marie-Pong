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
    Paddle,
    Ball,
    Brick,
    None
};

class GameObject {
private:
protected:
    static map<string, GameObject*> GameObjectList;
    Rectangle rect;
public:
    bool enabled{ false };
    bool hasCollision{ true };
    bool needToDestroy{ false };

    string name{ "" };
    Vector2 position{ 0,0 };
    Vector2 size{ 0,0 };
    Texture2D* sprite{};
    Color color{WHITE};
    GameObjectType type{ GameObjectType::None};

private:
protected:
    void CreateRect();

public:
    GameObject();
    GameObject(bool _enabled, string _name, Vector2 _pos, Vector2 _size, Texture2D* _sprite, GameObjectType _type);
    virtual ~GameObject();
    
    virtual void Update();
    virtual void Draw();
    //Put the object on the Destroy list for next Update
    void Destroy(); 

    //Mouse Gestion
    bool IsCursorInBounds();
    virtual int Clicked();

    //Collision Gestion
    virtual void Collided();

    static void CreateGameObject(const string id, GameObject* gO);

    static GameObject* GetGameObjectWithName(string _name);
    static vector<GameObject*> GetAllGameObjects();
    static vector<GameObject*> GetAllGameObjectsWith(GameObjectType type);
    
    static void DestroyGameObjectList();
};