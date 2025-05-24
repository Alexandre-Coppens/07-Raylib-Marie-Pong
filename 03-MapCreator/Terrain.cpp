#include "Terrain.h"

map<int, string> Terrain::dictionary;
vector<vector<Terrain::Tile>> Terrain::terrain;
Vector2 Terrain::tileSize{ 50,50 };
Vector2 Terrain::position{ 0,0 };
short Terrain::maxLayer{ 5 };

Terrain::Terrain() {
}

Terrain::~Terrain(){
}

void Terrain::Update()
{
}

void Terrain::AddNewTile(int layer,  int rotation, Vector2 pos, string name) {
	int index = CheckInDictionary(name);

	if (terrain.size() < maxLayer) {
		terrain.resize(maxLayer);
	}

	if (terrain[layer].size() == 0) {
		terrain[layer].push_back(Tile{ pos, (short)layer, rotation, index });
		return;
	}

	for (auto it = terrain[layer].begin(); it != terrain[layer].end();) {
		if (Vector2Equals(it->position, pos)) {
			terrain[layer].erase(it);
			break;
		}
		else it++;
	}

	terrain[layer].push_back(Tile{ pos, (short)layer, rotation, index });
}

void Terrain::RemoveTile(){
}

int Terrain::CheckInDictionary(string name) {
	for (auto d : dictionary) {
		if (name == d.second) {
			return d.first;
		}
	}
	int newInt = (int)dictionary.size();
	dictionary[newInt] = name;
	return newInt;
}