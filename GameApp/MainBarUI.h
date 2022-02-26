#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν : 
class WzUIRenderer;
class MainBarUI : public GameEngineActor
{
private:	// member Var
	WzUIRenderer* ExpBarUI_;
	WzUIRenderer* StatusUI_;
	WzUIRenderer* CashShopUI_;

public: // constrcuter destructer
	MainBarUI();
	~MainBarUI();

public: // delete Function
	MainBarUI(const MainBarUI& _other) = delete; 
	MainBarUI(MainBarUI&& _other) noexcept = delete;
	MainBarUI& operator=(const MainBarUI& _other) = delete;
	MainBarUI& operator=(const MainBarUI&& _other) = delete;

private:
	void CreateWzRenderer();

public:
	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;
};

