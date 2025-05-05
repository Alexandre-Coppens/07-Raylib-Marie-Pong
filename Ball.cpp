#include "Ball.h"

Ball::Ball(){
}

Ball::Ball(Vector2 _pos, Vector2 _size, Color _color){
	enabled = true;
	position = _pos;
	size = _size;
	color = _color;
	direction = RAYMATH_H::Vector2Normalize(Vector2{ float((rand()-0.5)*2),float((rand() - 0.5) * 2) });
}

Ball::~Ball(){
}

void Ball::Update() {
	float deltaSpeed = speed * GetFrameTime();
	if (position.x + size.x > GetScreenWidth() || position.x < 0) direction.x *= -1;
	if (position.y + size.y > GetScreenHeight() || position.y < 0) direction.y *= -1;

	for (auto go : GameObjectList) {
		if (go.second != this) {
			if (position.x < go.second->position.x + go.second->size.x &&
				position.x + size.x > go.second->position.x &&
				position.y < go.second->position.y + go.second->size.y &&
				position.y + size.y > go.second->position.y) direction.y *= -1;
		}
	}

	position.x += direction.x * deltaSpeed;
	position.y += direction.y * deltaSpeed;
}

void Ball::Draw(){
	DrawCircleV(Vector2{ position.x + (size.x * 0.5f), position.y + (size.y * 0.5f) }, size.x * 0.5f, color);
}