#include "Brick.h"
#include "Bonus.h"

using std::to_string;

Brick::Brick(){
}

Brick::Brick(Vector2 _pos, Vector2 _size, Color _color){
	enabled = true;
	position = _pos;
	size = _size;
	color = _color;
	CreateRect();
	sprite = &AssetList::SpriteList[""];
	type = GameObjectType::Brick;
}

Brick::~Brick(){
}

void Brick::Draw(){
	DrawTextureRec(*sprite, rect, position, color);
}

void Brick::Update(){
}

void Brick::Collided(){
	enabled = false;
	if (color.r+color.g+color.b == GREEN.r+ GREEN.g+ GREEN.b) {
		GameObject::CreateGameObject("Bonus" + to_string(std::rand()), new Bonus(position, size, WHITE));
	}
}

