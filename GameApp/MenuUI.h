#pragma once
#include "GameEngine/GameEngineActor.h"

// ���� : 
class MenuUI : public GameEngineActor
{
public:
	MenuUI();
	~MenuUI();

	void Start() override;
	void Update(float _DeltaTime) override;

protected:
	MenuUI(const MenuUI& _other) = delete; 
	MenuUI(MenuUI&& _other) noexcept = delete;
	MenuUI& operator=(const MenuUI& _other) = delete;
	MenuUI& operator=(const MenuUI&& _other) = delete;

private:

};

