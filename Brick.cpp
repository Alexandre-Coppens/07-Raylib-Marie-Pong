#include "Brick.h"

Brick::Brick(){
}

Brick::Brick(Vector2 _pos, Vector2 _size, Color _color){
	enabled = true;
	position = _pos;
	size = _size;
	color = _color;
	CreateRect();
	sprite = &AssetList::SpriteList[""];
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
}

