#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν : 
class ItemUI : public GameEngineActor
{
public:
	ItemUI();
	~ItemUI();

	void Start() override;
	void Update(float _DeltaTime) override;

protected:
	ItemUI(const ItemUI& _other) = delete; 
	ItemUI(ItemUI&& _other) noexcept = delete;
	ItemUI& operator=(const ItemUI& _other) = delete;
	ItemUI& operator=(const ItemUI&& _other) = delete;

private:
	void CreateRenderer();
};

