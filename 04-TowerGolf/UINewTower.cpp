#include "UINewTower.h"
#include "Tower.h"
#include "Terrain.h"
#include <iostream>
#include "Player.h"

using std::to_string;

UINewTower::UINewTower(TowerType _towerType):
	Actor(Vector2Zero(), Terrain::tileSize, ActorType::UINewTower),
	towerType(_towerType)
{
	sprite = TowerBible::GetTowerSkin(towerType);
}

UINewTower::~UINewTower(){
}

void UINewTower::Start(){
}

void UINewTower::Update(Vector2* scroll){
	position = GetMousePosition();
	CheckCanBePlaced(scroll);
	if (IsMouseButtonPressed(0)) PlaceTower(scroll);
	if (IsMouseButtonPressed(1)) Destroy();
}

void UINewTower::Draw(Vector2* scroll){
	if (towerType == TowerType::PirateBoat || towerType == TowerType::Moai || towerType == TowerType::Volcano) {
		color.a = 50;
		DrawCircleV(GetMousePosition(), TowerBible::GetTowerStats(towerType).range, color);
	}

	color.a = 255;
	Rectangle source{ 0, 0, sprite->width, sprite->height };
	Rectangle dest{ position.x, position.y, size.x, size.y };
	DrawTexturePro(*sprite, source, dest, Vector2{ size.x * 0.5f, size.y * 0.5f }, 0, color);
}

void UINewTower::PlaceTower(Vector2* scroll) {
	if (color.r == GREEN.r) {
		Vector2 mPos{ (int)floor((GetMouseX() + scroll->x) / Terrain::tileSize.x) * Terrain::tileSize.x + Terrain::tileSize.x * 0.5f, (int)floor((GetMouseY() + scroll->y) / Terrain::tileSize.y) * Terrain::tileSize.y + Terrain::tileSize.y * 0.5f };
		Actor::CreateActor("Tower_" + to_string((int)towerType) + "_" + to_string(std::rand()), 5, new Tower(mPos, Terrain::tileSize, towerType));
		Player::money -= TowerBible::GetTowerPrice(towerType);
		Destroy();
	}
	else {
		std::cout << "Obstructed \n ";
	}
}

void UINewTower::CheckCanBePlaced(Vector2* scroll) {
	short isOnPath = CheckTile(scroll);

	if (isOnPath == 2) {
		switch (towerType)
		{
		case TowerType::Windmill:
			color = GREEN;
			break;
		case TowerType::Volcano:
			color = GREEN;
			break;
		default:
			color = RED;
			break;
		}
	}
	else if (isOnPath == 1) {
		switch (towerType)
		{
		case TowerType::Dinosaur:
			color = GREEN;
			break;
		case TowerType::Moai:
			color = GREEN;
			break;
		default:
			color = RED;
			break;
		}
	}
	else if (isOnPath == 3) {
		switch (towerType)
		{
		case TowerType::PirateBoat:
			color = GREEN;
			break;
		default:
			color = RED;
			break;
		}
	}
	else color = RED ;

	Actor* ui = GetActorWithName("UIBackground");
	if (GetMouseX() >= ui->position.x && GetMouseX() <= ui->position.x + ui->size.x && GetMouseY() >= ui->position.y && GetMouseY() <= ui->position.y + ui->size.y) {
		color = RED;
	}
}

//0 = no, 1 = grass, 2 = path, 3 = water
short UINewTower::CheckTile(Vector2* scroll) {
	Vector2 pathPosition;
	Vector2 mPos{ (int)floor((GetMouseX() + scroll->x) / Terrain::tileSize.x), (int)floor((GetMouseY() + scroll->y) / Terrain::tileSize.y) };
	vector<Terrain::Tile*> tiles = Terrain::GetEveryTilesWithModifier("Path");
	for (int i = 0; i < tiles.size(); i++) {
		pathPosition = tiles[i]->position;
		if (Vector2Equals(pathPosition, mPos)) {
			return 2;
			break;
		}
	}

	tiles = Terrain::GetEveryTilesWithModifier("Grass");
	for (int i = 0; i < tiles.size(); i++) {
		pathPosition = tiles[i]->position;
		if (Vector2Equals(pathPosition, mPos)) {
			return 1;
			break;
		}
	}

	tiles = Terrain::GetEveryTilesWithModifier("Water");
	for (int i = 0; i < tiles.size(); i++) {
		pathPosition = tiles[i]->position;
		if (Vector2Equals(pathPosition, mPos)) {
			return 3;
			break;
		}
	}
}