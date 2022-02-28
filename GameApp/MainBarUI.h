#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν : 
class WzUIRenderer;
class MainBarUI : public GameEngineActor
{
public:
	MainBarUI();
	~MainBarUI();

	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;

protected:
	MainBarUI(const MainBarUI& _other) = delete; 
	MainBarUI(MainBarUI&& _other) noexcept = delete;
	MainBarUI& operator=(const MainBarUI& _other) = delete;
	MainBarUI& operator=(const MainBarUI&& _other) = delete;

private:
	void CreateWzRenderer();

	WzUIRenderer* ExpBarUI_;
	WzUIRenderer* StatusUI_;
	WzUIRenderer* CashShopUI_;
};

