#pragma once

#include <vector>
#include "Raylib.h"
#include "AssetsList.h"
#include "Actor.h"
#include "Terrain.h"

using std::vector;

static void DrawScreen(Vector2* scroll);

//Draw the terrain and the gameObjects on screen
static void DrawScreen(Vector2* scroll){
	vector<vector<Actor*>>* goList = Actor::GetAllActorsLayered();
	vector<vector<Terrain::Tile>>* terrain = &Terrain::terrain;

	short max = fmax(terrain->size(), goList->size());
	for (int i = 0; i < max; i++) {
		if (i < terrain->size()) {
			if ((*terrain)[i].size() > 0) {
				for (Terrain::Tile tile : (*terrain)[i]) {
					if (tile.position.x * Terrain::tileSize.x > scroll->x - Terrain::tileSize.y &&
								tile.position.x * Terrain::tileSize.x < scroll->x + GetScreenWidth() &&
								tile.position.y * Terrain::tileSize.y > scroll->y - Terrain::tileSize.y &&
								tile.position.y * Terrain::tileSize.y < scroll->y + GetScreenHeight()) {
						Texture2D* sprite = &AssetList::SpriteList[Terrain::dictionary[tile.dictionaryTexture]];
						DrawTexturePro(*sprite,
							Rectangle{ 0, 0, (float)sprite->width, (float)sprite->height },
							Rectangle{ (tile.position.x * Terrain::tileSize.x)- scroll->x + Terrain::tileSize.x * 0.5f, (tile.position.y * Terrain::tileSize.y)- scroll->y + Terrain::tileSize.y * 0.5f, Terrain::tileSize.x, Terrain::tileSize.y },
							Vector2{ Terrain::tileSize.x * 0.5f, Terrain::tileSize.y * 0.5f },
							tile.rotation,
							WHITE);
					}
				}
			}
		}

		if (goList->size() > i) {
			for (Actor* go : (*goList)[i]) {
				if (go->enabled) go->Draw(scroll);
			}
		}
	}
}