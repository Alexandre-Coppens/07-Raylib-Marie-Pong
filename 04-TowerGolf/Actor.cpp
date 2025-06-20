#include "Actor.h"
#include "GolfBall.h"

map<string, Actor*> Actor::ActorList;
vector<vector<Actor*>> Actor::ActorsByLayer;

Actor::Actor(Vector2 _pos, Vector2 _size, ActorType _type, Texture2D* _sprite, Color _color):
	position(_pos),
	size(_size),
	type(_type),
	sprite(_sprite),
	color(_color),
	name(""),
	enabled(true)
{
}

Actor::~Actor(){
	ActorList.erase(name);
}

void Actor::Start() {
}

void Actor::Update(Vector2* scroll) {
}

//Only change Draw Function if it's not affected by scroll or others.
void Actor::Draw(Vector2* scroll) {
	Rectangle source{ 0, 0, sprite->width, sprite->height };
	Rectangle dest{ position.x - scroll->x, position.y - scroll->y, size.x, size.y };
	DrawTexturePro(*sprite, source, dest, Vector2{ size.x * 0.5f, size.y * 0.5f }, 0, color);
}

void Actor::Collided(){
}

void Actor::CreateActor(const string id, int layer,Actor* actor){
	actor->name = id;
	ActorList[id] = actor;
	if (ActorsByLayer.size() < layer+1) {
		ActorsByLayer.resize(layer+1);
	}
	ActorsByLayer[layer].push_back(actor);
}

Actor* Actor::GetActorWithName(string _name) {
	for (auto const& i : ActorList) {
		if (i.first == _name) {
			return const_cast<Actor*>(i.second);
		}
	}
	return nullptr;
}

vector<Actor*> Actor::GetAllActors(){
	vector<Actor*> ret;
	for (auto const& i : ActorList) {
		ret.push_back(const_cast<Actor*>(i.second));
	}
	return ret;
}

vector<vector<Actor*>>* Actor::GetAllActorsLayered(){
	return &ActorsByLayer;
}

vector<Actor*> Actor::GetAllActorsWith(ActorType type){
	vector<Actor*> ret;
	for(auto const& i : ActorList){
		if (i.second->type == type) {
			ret.push_back(const_cast<Actor*>(i.second));
		}
	}
    return ret;
}

void Actor::DestroyActorList(){
	ActorList.clear();
}

void Actor::Clicked() {
}

void Actor::Destroy() {
	needToDestroy = true;
}

void Actor::RemoveActorFromLists(Actor* actor) {
	auto iteratorList = ActorList.find(actor->name);
	if (iteratorList != ActorList.end()) {
		ActorList.erase(iteratorList);
	}

	for (int i = 0; i < ActorsByLayer.size(); i++) {
		auto iteratorLayer = find(ActorsByLayer[i].begin(), ActorsByLayer[i].end(), actor);
		if (iteratorLayer != ActorsByLayer[i].end()) {
			ActorsByLayer[i].erase(iteratorLayer);
		}
	}

	delete actor;
}