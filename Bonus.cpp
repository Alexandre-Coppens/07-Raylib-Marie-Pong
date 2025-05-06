#include "Bonus.h"
#include "Ball.h"
#include "Paddle.h"

using std::to_string;

Bonus::Bonus(){
}

Bonus::Bonus(Vector2 _pos, Vector2 _size, Color _color){
	enabled = true;
	hasCollision = false;
	position = _pos;
	size = _size;
	color = _color;
	CreateRect();
	sprite = &AssetList::SpriteList[""];
}

Bonus::~Bonus(){
}

void Bonus::Draw(){
	DrawTextureRec(*sprite, rect, position, color);
}

void Bonus::Update(){
	position.y += speed * GetFrameTime();
	for (auto go : GameObjectList) {
		if (go.second != this && go.second->enabled && go.second->hasCollision) {
			if (position.x < go.second->position.x + go.second->size.x &&
				position.x + size.x > go.second->position.x &&
				position.y < go.second->position.y + go.second->size.y &&
				position.y + size.y > go.second->position.y)
			{
				if (dynamic_cast<Paddle*>(go.second)) {
					GameObject::CreateGameObject("Ball" + to_string(std::rand()), new Ball(Vector2{ go.second->position.x , go.second->position.y - 20 }, Vector2{ 20,20 }, RED));
					needToDestroy = true;
				}
			}
		}
	}
}
