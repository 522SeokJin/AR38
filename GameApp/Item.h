#pragma once
#include <GameEngine/GameEngineActor.h>

struct ItemInfo
{
	int REQLevel_;
	int StarForce_;
	int Upgrade_;
	int STR_;
	int DEX_;
	int INT_;
	int LUK_;
	int MaxHP_;
	int MaxMP_;
	int Power_;
	int Magic_;
};

// Ό³Έν : 
class Item : public GameEngineActor
{
public:
	Item();
	~Item();

	void Start() override;
	void Update(float _DeltaTime) override;

protected:
	Item(const Item& _other) = delete; 
	Item(Item&& _other) noexcept = delete;
	Item& operator=(const Item& _other) = delete;
	Item& operator=(const Item&& _other) = delete;

private:
	ItemInfo Info_;
};

