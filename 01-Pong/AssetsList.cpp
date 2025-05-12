#include "AssetsList.h"

Texture2D AssetList::textureTemp;
Music AssetList::music;
AssetList* AssetList::instance = nullptr;
map<string, Font> AssetList::textFont;
map<string, Texture2D> AssetList:: SpriteList;
map<string, Sound> AssetList:: soundList;

AssetList::AssetList() {
    if (SpriteList.size() > 0) return;
    LoadTexture2D("", "resources/Unknown.png");

    textFont["Alagard"] = LoadFont("resources/fonts/alagard.png");
    textFont["Alpha-Beta"] = LoadFont("resources/fonts/alpha_beta.png");
    textFont["Jupiter-Crash"] = LoadFont("resources/fonts/jupiter_crash.png");
    textFont["Mecha"] = LoadFont("resources/fonts/mecha.png");
    textFont["Pixantiqua"] = LoadFont("resources/fonts/pixantiqua.png");
    textFont["Pixelplay"] = LoadFont("resources/fonts/pixelplay.png");
    textFont["Romulus"] = LoadFont("resources/fonts/romulus.png");
    textFont["Setback"] = LoadFont("resources/fonts/setback.png");

    music = LoadMusicStream("resources/Balatro.mp3");
    soundList["Hit"] = LoadSound("resources/HitSound.wav");

    SetMusicVolume(music, 2);
    PlayMusicStream(music);
}

AssetList::~AssetList(){
}

void AssetList::LoadTexture2D(string name, string link){
    Image temp = LoadImage(link.c_str());
    textureTemp = LoadTextureFromImage(temp);
    SpriteList[name] = textureTemp;
    UnloadImage(temp);
}

AssetList* AssetList::GetInstance() {
    if (instance == nullptr) {
        instance = new AssetList();
    }
    return instance;
}
