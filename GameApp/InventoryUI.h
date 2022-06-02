#pragma once
#include "GameEngine/GameEngineActor.h"

enum class InventoryTab
{
	Equipment,
	Useable,
	Etc,
};

// 설명 : 
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

	inline void AddMeso(int _Value)
	{
		Meso_ += _Value;
	}
	inline void SetMeso(int _Value)
	{
		Meso_ = _Value;
	}

	inline int GetMeso()
	{
		return Meso_;
	}

	void AddRedPotion();
	void AddBluePotion();
	void AddElixirPotion();
	
	inline void SetRedPotion(int _Value) {RedPotionCount_ = _Value; };
	inline void SetBluePotion(int _Value) { BluePotionCount_ = _Value; };
	inline void SetElixirPotion(int _Value) { ElixirPotionCount_ = _Value; };

	inline int GetRedPotionCount()
	{
		return RedPotionCount_;
	}
	inline int GetBluePotionCount()
	{
		return BluePotionCount_;
	}
	inline int GetElixirPotionCount()
	{
		return ElixirPotionCount_;
	}

	inline void SubRedPotionCount()
	{
		--RedPotionCount_;
	}
	inline void SubBluePotionCount()
	{
		--BluePotionCount_;
	}
	inline void SubElixirPotionCount()
	{
		--ElixirPotionCount_;
	}

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

	// 아이템갯수 최대치 99
	std::map<int, std::vector<GameEngineUIRenderer*>> RedPotionNumber_;
	std::map<int, std::vector<GameEngineUIRenderer*>> BluePotionNumber_;
	std::map<int, std::vector<GameEngineUIRenderer*>> ElixirPotionNumber_;

	GameEngineCollision* EquipmentTab_;
	GameEngineCollision* UseableTab_;
	GameEngineCollision* EtcTab_;

	InventoryTab EnabledTab_;

	int Meso_;
	
};

