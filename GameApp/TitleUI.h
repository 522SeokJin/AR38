#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν : 
class GameEngineCollision;
class GameEngineUIRenderer;
class TitleUI : public GameEngineActor
{
public:
	TitleUI();
	~TitleUI();

	void Start() override;
	void Update(float _DeltaTime) override;

protected:
	TitleUI(const TitleUI& _other) = delete; 
	TitleUI(TitleUI&& _other) noexcept = delete;
	TitleUI& operator=(const TitleUI& _other) = delete;
	TitleUI& operator=(const TitleUI&& _other) = delete;

private:
	void MouseEvent(GameEngineCollision* _OtherCollision);

	GameEngineUIRenderer* LoginRenderer_;
	GameEngineCollision* LoginButton_;
};

