#include "Paddle.h"

Paddle::Paddle(){
}

Paddle::Paddle(Vector2 _pos, Vector2 _size, Color _color){
	enabled = true;
	position = _pos;
	size = _size;
	color = _color;
	CreateRect();
	sprite = &AssetList::SpriteList[""];
	type = GameObjectType::Paddle;
}

Paddle::~Paddle(){
}

void Paddle::Update() {
	if (IsKeyDown(KEY_LEFT) && position.x > 0) {
		position.x -= speed * GetFrameTime();
	}
	if (IsKeyDown(KEY_RIGHT) && position.x + size.x < GetScreenWidth()) {
		position.x += speed * GetFrameTime();
	}
}

void Paddle::Draw(){
	DrawTextureRec(*sprite, rect, position, color);

}