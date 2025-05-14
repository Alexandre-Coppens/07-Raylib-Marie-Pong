#include "Car.h"

using std::to_string;

Car::Car(){
}

Car::Car(Vector2 _pos, Vector2 _size, Color _color){
	sprite = &AssetList::SpriteList["SpriteSheet_Car"];
	position = _pos;
	size = _size;
	color = _color;
	type = GameObjectType::Car;
	CreateRect();
}

Car::~Car(){
}

void Car::Update(){
	towardSpeed = 0;
	isAccelerating = false;

	if (IsKeyDown(KEY_UP)) {
		towardSpeed = maxSpeed.x ;
		isAccelerating = true;
	}
	else if (IsKeyDown(KEY_DOWN)) {
		towardSpeed = maxSpeed.y;
		isAccelerating = true;
	}
	if (IsKeyDown(KEY_LEFT) && abs(speed) >= minTurnSpeed ) {
		rotation += turnRate * PI * GetFrameTime();
	}
	if (IsKeyDown(KEY_RIGHT) && abs(speed) >= minTurnSpeed) {
		rotation -= turnRate * PI * GetFrameTime();
	}

	speed = Lerp(speed, towardSpeed, (isAccelerating ? thrust : decay) * GetFrameTime());

	deltaSpeed.x = sin(rotation) * -speed * GetFrameTime();
	deltaSpeed.y = cos(rotation) * -speed * GetFrameTime();

	position.x += deltaSpeed.x;
	position.y += deltaSpeed.y;
}

void Car::Draw() {
	CarSide();
	Vector2 posInSprite{ 
		sprite->width * currentSprite.x * 0.33f , 
		sprite->height * currentSprite.y * 0.33f 
	};

	Rectangle source = { posInSprite.x, posInSprite.y, sprite->width * 0.33f * ((flipX || speed < 0) && !(!flipX && speed < 0) ? -1 : 1), sprite->height * 0.33f};
	Rectangle dest = { position.x, position.y, size.x, size.y };
	DrawTexturePro(*sprite, source, dest, Vector2Zero(), 0, color);
	DrawText(to_string(speed).c_str(), 10, 10, 20, GRAY);
}

void Car::CarSide() {
	Vector2 ndeltaSpeed = Vector2Normalize(deltaSpeed);
	 float dot = Vector2DotProduct( ndeltaSpeed, Vector2{0,1});
	 dot += 1;
	 dot *= 0.5f;
	 dot *= 8;
	 const int idot = static_cast<int>(dot + 0.5f);
	 currentSprite = { static_cast<float>(idot % 3), static_cast<float>(idot / 3) };

	 flipX = Vector2DotProduct(ndeltaSpeed, Vector2{ 1,0 }) <= 0;
}
