#include "GameObject.h"

map<string, GameObject*> GameObject::GameObjectList;

GameObject::GameObject(){
	CreateRect();
}

GameObject::GameObject(bool _enabled, string _name, Vector2 _pos, Vector2 _size, Texture2D* _sprite, GameObjectType _type) {
	enabled = _enabled;
	name = _name;
	position = _pos;
	size = _size;
	sprite = _sprite;
	type = _type;

	CreateRect();
}

GameObject::~GameObject(){
}

void GameObject::Update() {
}

void GameObject::Draw() {
	DrawTextureRec(*sprite, rect, position, WHITE);
}

bool GameObject::IsCursorInBounds(){
	if (!enabled)return false;
	return GetMouseX() >= position.x && GetMouseX() <= position.x + size.x && GetMouseY() >= position.y && GetMouseY() <= position.y + size.y;
}

void GameObject::CreateRect(){
	rect.x = 0;
	rect.y = 0;
	rect.width = size.x;
	rect.height = size.y;
}

void GameObject::Collided(){
}

void GameObject::CreateGameObject(const string id, GameObject* gO){
	gO->name = id;
	GameObjectList[id] = gO;
}

GameObject* GameObject::GetGameObjectWithName(string _name) {
	for (auto const& i : GameObjectList) {
		if (i.first == _name) {
			return const_cast<GameObject*>(i.second);
		}
	}
	return nullptr;
}

vector<GameObject*> GameObject::GetAllGameObjects()
{
	vector<GameObject*> ret;
	for (auto const& i : GameObjectList) {
		ret.push_back(const_cast<GameObject*>(i.second));
	}
	return ret;
}

vector<GameObject*> GameObject::GetAllGameObjectsWith(GameObjectType type){
	vector<GameObject*> ret;
	for(auto const& i : GameObjectList){
		if (i.second->type == type) {
			ret.push_back(const_cast<GameObject*>(i.second));
		}
	}
    return ret;
}

int GameObject::Clicked() {
	return 0;
}