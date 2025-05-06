#include "Bonus.h"

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
}
