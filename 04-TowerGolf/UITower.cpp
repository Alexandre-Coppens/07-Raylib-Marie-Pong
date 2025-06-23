#include <iostream>
#include <string>
#include "UITower.h"
#include "UINewTower.h"
#include "AssetsList.h"

using std::string;
using std::cout;
using std::to_string;

UITower::UITower(Vector2 _pos, Vector2 _size, TowerType _towerType) :
	Actor(_pos, _size, ActorType::UI),
	towerType(_towerType)
{
	sprite = TowerBible::GetTowerSkin(towerType);
}

UITower::~UITower(){
}

void UITower::Start(){
}

void UITower::Update(Vector2* scroll){
}

void UITower::Draw(Vector2* scroll){
	Rectangle source{ 0, 0, sprite->width, sprite->height };
	Rectangle dest{ position.x, position.y, size.x, size.y };
	DrawTexturePro(*sprite, source, dest, Vector2{ size.x * 0.5f, size.y * 0.5f }, 0, color);

	if (isHovered) {
		Texture2D* background = &AssetList::SpriteList["Button"];
		source = Rectangle{ 0, 0, (float)background->width, (float)background->height };
		dest = Rectangle{ position.x + 100, position.y -25, 125, 75 };
		DrawTexturePro(*background, source, dest, Vector2{size.x * 0.5f, size.y * 0.5f}, 0, color);
		DrawTextEx(AssetList::textFont["pixantiqua"], to_string(TowerBible::GetTowerPrice(towerType)).c_str(), Vector2{ dest.x + 10, dest.y + 10 }, 20, 5, YELLOW);
	
	}
	isHovered = false;
}

void UITower::MouseHover() {
	isHovered = true;
}

void UITower::Clicked() {
	for (auto oldChoice : GetAllActorsWith(ActorType::UINewTower)) {
		oldChoice->Destroy();
	}
	CreateActor("UINewTower" + to_string(std::rand()), 12, new UINewTower(towerType));
}