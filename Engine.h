#pragma once

#include <string>
#include <vector>
#include "AssetsList.h"

using std::string;
using std::vector;

class Engine {
private:
	AssetList* assets{};

public:
	Engine();
	void Start();
	void Update();
	void Draw();

private:
};
