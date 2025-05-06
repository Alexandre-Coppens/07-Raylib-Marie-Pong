#include "Ball.h"
#include "Paddle.h"

Ball::Ball(){
}

Ball::Ball(Vector2 _pos, Vector2 _size, Color _color){
	enabled = true;
	hasCollision = false;
	position = _pos;
	size = _size;
	color = _color;
	direction = RAYMATH_H::Vector2Normalize(Vector2{ float((rand()-0.5)*2),float((rand() - 0.5) * 2) });
	direction.x = Clamp(direction.x, -0.33f, 0.33f);
	direction = Vector2Normalize(direction);
	type = GameObjectType::Ball;
}

Ball::~Ball(){
}

void Ball::Update() {
	speed = Lerp(speed, 400, 5 * GetFrameTime());
	float deltaSpeed = speed * GetFrameTime();
	if (position.x + size.x > GetScreenWidth() || position.x < 0) direction.x *= -1;
	if (position.y < 0) direction.y *= -1;
	if (position.y + size.y > GetScreenHeight()) {
		needToDestroy = true;
		};

	for (auto go : GameObjectList) {
		if (go.second != this && go.second->enabled && go.second->hasCollision) {
			if (position.x < go.second->position.x + go.second->size.x &&
				position.x + size.x > go.second->position.x &&
				position.y < go.second->position.y + go.second->size.y &&
				position.y + size.y > go.second->position.y) 
			{
				soundPitch += 1.0f;
				SetSoundPitch(AssetList::soundList["Hit"], soundPitch);
				if (dynamic_cast<Paddle*>(go.second)) {
					direction.x += (((position.x + (size.x * 0.5f)) - go.second->position.x) / go.second->size.x - 0.5f) * 2;
					direction = Vector2Normalize(direction);
					direction.x = Clamp(direction.x, -0.33f, 0.33f);
					direction = Vector2Normalize(direction);
					soundPitch = 1;
					SetSoundPitch(AssetList::soundList["Hit"], soundPitch);
				}
				float xstart = std::max(position.x, go.second->position.x);
				float xend = std::min(position.x + size.x, go.second->position.x + go.second->size.x);
				float ystart = std::max(position.y, go.second->position.y);
				float yend = std::min(position.y + size.y, go.second->position.y + go.second->size.y);
				if (xend - xstart > yend - ystart) {
					direction.y *= -1;
					position.y += direction.y * deltaSpeed;
				}
				else {
					direction.x *= -1;
					position.x += direction.x * deltaSpeed;
				}
				speed += 400;
				go.second->Collided();
				PlaySound(AssetList::soundList["Hit"]);
			}
		}
	}

	position.x += direction.x * deltaSpeed;
	position.y += direction.y * deltaSpeed;
}

void Ball::Draw(){
	DrawCircleV(Vector2{ position.x + (size.x * 0.5f), position.y + (size.y * 0.5f) }, size.x * 0.5f, color);
}