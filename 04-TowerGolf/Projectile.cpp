#include "Projectile.h"
#include "GolfBall.h"
#include "AssetsList.h"

Projectile::Projectile(Vector2 _pos, Vector2 _size, Actor* _target) :
	Actor(_pos, _size),
	target( _target)
{
	sprite = &AssetList::SpriteList["Unknown"];
}

Projectile::~Projectile(){
}

void Projectile::Start(){
	Actor::Start();
}
void Projectile::Update(Vector2* scroll){
	position = Vector2MoveTowards(position, target->position, speed);
	Rectangle collider = Rectangle{ position.x - size.x *0.5f, position.y - size.y * 0.5f, size.x, size.y };
	vector<Actor*> hits = GetAllActorsInCollisionRect(collider);

	for (auto i : hits) {
		if (GolfBall* ball = dynamic_cast<GolfBall*>(i)) {
			ball->ApplyDamage();
			Destroy();
			break;
		}
	}
}
void Projectile::Draw(Vector2* scroll){
	Actor::Draw(scroll);
}