#include <iostream>
#include <fstream>

#include "Terrain.h"

using std::ofstream;
using std::ifstream;
using std::getline;
using std::to_string;
using std::cout;

map<int, string> Terrain::dictionary;
vector<vector<Terrain::Tile>> Terrain::terrain;
Vector2 Terrain::tileSize{ 45,45 };
Vector2 Terrain::position{ 0,0 };
short Terrain::maxLayer{ 5 };

Terrain::Terrain() {
}

Terrain::~Terrain(){
}

void Terrain::Update(){
}

vector<Terrain::Tile*> Terrain::GetEveryTilesWithModifier(string m){
	vector<Tile*> tiles;
	for (int i = 0; i < terrain.size(); i++) {
		for (int j = 0; j < terrain[i].size(); j++) {
			if (terrain[i][j].modifier == m) tiles.push_back(&terrain[i][ j]);
		}
	}
	return tiles;
}

void Terrain::AddNewTile(int layer,  int rotation, Vector2 pos, string name, string modifier) {
	int index = CheckInDictionary(name);

	if (terrain.size() < maxLayer) {
		terrain.resize(maxLayer);
	}

	if (terrain[layer].size() == 0) {
		terrain[layer].push_back(Tile{ pos, (short)layer, rotation, index, modifier });
		return;
	}

	for (auto it = terrain[layer].begin(); it != terrain[layer].end();) {
		if (Vector2Equals(it->position, pos)) {
			terrain[layer].erase(it);
			break;
		}
		else it++;
	}

	terrain[layer].push_back(Tile{ pos, (short)layer, rotation, index, modifier });
}

void Terrain::RemoveTile(int layer,  Vector2 pos){
	if (terrain.size() < maxLayer) {
		return;
	}

	if (terrain[layer].size() == 0) {
		return;
	}

	for (auto it = terrain[layer].begin(); it != terrain[layer].end();) {
		if (Vector2Equals(it->position, pos)) {
			terrain[layer].erase(it);
			break;
		}
		else it++;
	}
}

void Terrain::AddToDictionary(int index, string name) {
	if (AssetList::SpriteList.find(name) == AssetList::SpriteList.end()) {
		dictionary[index] = "Unknown";
	}
	else {
		dictionary[index] = name;
	}
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

void Terrain::LoadMap(string fileName){
	dictionary.clear();
	terrain.clear();

	string line;
	ifstream loadFile(fileName + ".txt");

	if (loadFile.is_open()) {
		while (getline(loadFile, line) ){
			if (line[0] == 'D') {
				vector<string> dict = BreakString(line, '$');
				dict = BreakString(dict[1], ':');
				AddToDictionary(stoi(dict[0]), dict[1]);
			}
			if (line[0] == 'T') {
				vector<string> tile = BreakString(line, '$');
				vector<string> posS = BreakString(tile[1], ':');
				Vector2 posV  { stof(posS[0]), stof(posS[1]) };
				string family = BreakString(dictionary[stoi(tile[4])], '_')[0];
				AddNewTile(stoi(tile[2]), stoi(tile[3]), posV, dictionary[stoi(tile[4])], family);
			}	
		}
		loadFile.close();
	}
	else {
		cout << "Could not load " + fileName + ".txt ." + "\n";
	}
}

vector<string> Terrain::BreakString(string str, char breacker) {
	vector<string> r;
	string word;
	for(int i = 0; i < str.size(); i++)
	{
		if (str[i] == breacker) {
			r.push_back(word);
			word.clear();
		}
		else{
			word += str[i];
		}
	}
	r.push_back(word);
	return r;
}