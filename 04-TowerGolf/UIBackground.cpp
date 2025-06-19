#include "UIBackground.h"

UIBackground::UIBackground() {
	sprite = &AssetList::SpriteList["Unknown"];
	position = Vector2{ 0, 0 };
	size = Vector2{ 100, (float)GetScreenHeight() };
	color = GRAY;
	type = GameObjectType::UI;
	layer = 10;
	CreateRect();
}

UIBackground::UIBackground(Vector2 _pos, Vector2 _size, Color color){
}

UIBackground::~UIBackground(){
}

void UIBackground::Start() {
}

void UIBackground::Update(Vector2* scroll) {
}

void UIBackground::Draw(Vector2* scroll) {
	Rectangle source{ 0, 0, sprite->width, sprite->height };
	Rectangle dest{ position.x , position.y, size.x, size.y };
	DrawTexturePro(*sprite, source, dest, Vector2{0, 0 }, 0, color);
}