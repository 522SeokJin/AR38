#pragma once
#include "GameEngine/GameEngineActor.h"

// 설명 : 
class GameEngineUIRenderer;
class QuickSlotUI : public GameEngineActor
{
public:
	QuickSlotUI();
	~QuickSlotUI();

	void Start() override;
	void Update(float _DeltaTime) override;

protected:
	QuickSlotUI(const QuickSlotUI& _other) = delete; 
	QuickSlotUI(QuickSlotUI&& _other) noexcept = delete;
	QuickSlotUI& operator=(const QuickSlotUI& _other) = delete;
	QuickSlotUI& operator=(const QuickSlotUI&& _other) = delete;

private:
	GameEngineUIRenderer* RedPotion_;
	GameEngineUIRenderer* BluePotion_;
	GameEngineUIRenderer* ElixirPotion_;

	// 아이템갯수 최대치 99
	std::map<int, std::vector<GameEngineUIRenderer*>> RedPotionNumber_;
	std::map<int, std::vector<GameEngineUIRenderer*>> BluePotionNumber_;
	std::map<int, std::vector<GameEngineUIRenderer*>> ElixirPotionNumber_;

};

