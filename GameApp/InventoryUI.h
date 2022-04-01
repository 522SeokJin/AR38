#pragma once
#include "GameEngine/GameEngineActor.h"

enum class InventoryCategory
{
	Equipment,
	Useable,
	Etc,
};

// Ό³Έν : 
class Item;
class GameEngineCollision;
class InventoryUI : public GameEngineActor
{
public:
	InventoryUI();
	~InventoryUI();

	void Start() override;
	void Update(float _DeltaTime) override;

protected:
	InventoryUI(const InventoryUI& _other) = delete;
	InventoryUI(InventoryUI&& _other) noexcept = delete;
	InventoryUI& operator=(const InventoryUI& _other) = delete;
	InventoryUI& operator=(const InventoryUI&& _other) = delete;

private:
	void CreateRenderer();

	void PushItem(InventoryCategory _Category, Item* _Item);

	void EraseItem(InventoryCategory _Category, int _Index);

	std::map<int, std::vector<Item*>> ItemList_;
	GameEngineCollision* TitleBar_;
	GameEngineCollision* Items_[32];
};

