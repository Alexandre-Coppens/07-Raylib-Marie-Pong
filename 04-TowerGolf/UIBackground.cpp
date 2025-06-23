#include "UIBackground.h"
#include "UITower.h"
#include "TowerBible.h"

UIBackground::UIBackground():
	Actor(Vector2{ 0, 0 }, Vector2{ 100, (float)GetScreenHeight() }, ActorType::UI, & AssetList::SpriteList["Button"], GRAY)
{
}

UIBackground::~UIBackground(){
}

void UIBackground::Start() {
	Actor::CreateActor("UITowerWindmill", 11, new UITower(Vector2{ 50, 60 }, Vector2{ 60,60 }, TowerType::Windmill));
	Actor::CreateActor("UIPirateBoat", 11, new UITower(Vector2{ 50, 60 * 3 }, Vector2{ 60,60 }, TowerType::PirateBoat));
	Actor::CreateActor("UIDinosaur", 11, new UITower(Vector2{ 50, 60 * 5 }, Vector2{ 60,60 }, TowerType::Dinosaur));
	Actor::CreateActor("UIVolcano", 11, new UITower(Vector2{ 50, 60 * 7 }, Vector2{ 60,60 }, TowerType::Volcano));
	Actor::CreateActor("UIMoai", 11, new UITower(Vector2{ 50, 60 * 9 }, Vector2{ 60,60 }, TowerType::Moai));
}

void UIBackground::Update(Vector2* scroll) {
}

void UIBackground::Draw(Vector2* scroll) {
	Rectangle source{ 0, 0, sprite->width, sprite->height };
	Rectangle dest{ position.x , position.y, size.x, size.y };
	DrawTexturePro(*sprite, source, dest, Vector2{0, 0 }, 0, color);
}