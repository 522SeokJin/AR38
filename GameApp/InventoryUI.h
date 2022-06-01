#pragma once
#include "GameEngine/GameEngineActor.h"

enum class InventoryTab
{
	Equipment,
	Useable,
	Etc,
};

// Ό³Έν : 
class GameEngineCollision;
class GameEngineUIRenderer;
class InventoryUI : public GameEngineActor
{
public:
	InventoryUI();
	~InventoryUI();

	void Start() override;
	void Update(float _DeltaTime) override;

	void AddMeso(int _Value)
	{
		Meso_ += _Value;
	}

	inline void AddRedPotionCount() { ++RedPotionCount_; }
	inline void AddBluePotionCount() { ++BluePotionCount_; }
	inline void AddElixirPotionCount() { ++ElixirPotionCount_; }
	inline void SubRedPotionCount() { --RedPotionCount_; }
	inline void SubBluePotionCount() { --BluePotionCount_; }
	inline void SubElixirPotionCount() { --ElixirPotionCount_; }

protected:
	InventoryUI(const InventoryUI& _other) = delete;
	InventoryUI(InventoryUI&& _other) noexcept = delete;
	InventoryUI& operator=(const InventoryUI& _other) = delete;
	InventoryUI& operator=(const InventoryUI&& _other) = delete;

private:
	void CreateRenderer();

	void TitleBarEvent(GameEngineCollision* _OtherCollision);

	void ChangeTabEvent();

	GameEngineCollision* TitleBar_;
	bool Grabbed_;

	GameEngineUIRenderer* EquipmentRenderer_;
	GameEngineUIRenderer* UseableRenderer_;
	GameEngineUIRenderer* EtcRenderer_;
	GameEngineUIRenderer* MesoText_;

	GameEngineUIRenderer* RedPotion_;
	GameEngineUIRenderer* BluePotion_;
	GameEngineUIRenderer* ElixirPotion_;
	int RedPotionCount_;
	int BluePotionCount_;
	int ElixirPotionCount_;

	GameEngineCollision* EquipmentTab_;
	GameEngineCollision* UseableTab_;
	GameEngineCollision* EtcTab_;

	InventoryTab EnabledTab_;

	GameEngineCollision* ItemBlocks_[32];
	
	int Meso_;
};

