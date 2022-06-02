#pragma once
#include "GameEngine/GameEngineActor.h"

enum class InventoryTab
{
	Equipment,
	Useable,
	Etc,
};

// ���� : 
class GameEngineCollision;
class GameEngineUIRenderer;
class GameEngineImageRenderer;
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

	void AddRedPotion();
	void AddBluePotion();
	void AddElixirPotion();

protected:
	InventoryUI(const InventoryUI& _other) = delete;
	InventoryUI(InventoryUI&& _other) noexcept = delete;
	InventoryUI& operator=(const InventoryUI& _other) = delete;
	InventoryUI& operator=(const InventoryUI&& _other) = delete;

private:
	void CreateRenderer();

	void TitleBarEvent(GameEngineCollision* _OtherCollision);

	void ChangeTabEvent();
	void UsePotionEvent();

	void UpdateEnableTabItem();

	GameEngineCollision* TitleBar_;
	bool Grabbed_;

	GameEngineUIRenderer* EquipmentRenderer_;
	GameEngineUIRenderer* UseableRenderer_;
	GameEngineUIRenderer* EtcRenderer_;
	GameEngineUIRenderer* MesoText_;

	GameEngineUIRenderer* RedPotion_;
	GameEngineUIRenderer* BluePotion_;
	GameEngineUIRenderer* ElixirPotion_;
	GameEngineCollision* RedPotionCollision_;
	GameEngineCollision* BluePotionCollision_;
	GameEngineCollision* ElixirPotionCollision_;

	int RedPotionCount_;
	int BluePotionCount_;
	int ElixirPotionCount_;

	// �����۰��� �ִ�ġ 99
	std::map<int, std::vector<GameEngineUIRenderer*>> RedPotionNumber_;
	std::map<int, std::vector<GameEngineUIRenderer*>> BluePotionNumber_;
	std::map<int, std::vector<GameEngineUIRenderer*>> ElixirPotionNumber_;

	GameEngineCollision* EquipmentTab_;
	GameEngineCollision* UseableTab_;
	GameEngineCollision* EtcTab_;

	InventoryTab EnabledTab_;

	int Meso_;
	
};

