#include "raylib.h"
#include <iostream>
#include <vector>

using std::vector;

class GameObject {
private:
	Vector2 position;
	Vector2 size;

public:
	static vector<GameObject*> gameObjectList;

public:
	GameObject(Vector2 _position, Vector2 _size) {
		position = _position;
		size = _size;
	}
	~GameObject();

	void Update();
	void Draw();

	void AddObjectToList(GameObject* go) { gameObjectList.push_back(go); }
	void RemoveObjectFromList(GameObject* go) { gameObjectList.erase(gameObjectList.); }
};

