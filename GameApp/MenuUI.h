#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν : 
class GameEngineUIRenderer;
class GameEngineCollision;
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
	void CharButtonEvent(GameEngineCollision* _OtherCollision);
	void SettingButtonEvent(GameEngineCollision* _OtherCollision);
	void MenuButtonEvent(GameEngineCollision* _OtherCollision);

	GameEngineUIRenderer* CharRenderer_;
	GameEngineUIRenderer* SettingRenderer_;
	GameEngineUIRenderer* MenuRenderer_;

	GameEngineCollision* CharCol_;
	GameEngineCollision* SettingCol_;
	GameEngineCollision* MenuCol_;
};

