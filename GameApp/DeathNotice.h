#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν : 
class GameEngineUIRenderer;
class GameEngineCollision;
class DeathNotice : public GameEngineActor
{
public:
	DeathNotice();
	~DeathNotice();
	
	void Start() override;
	void Update(float _DeltaTime) override;

protected:
	DeathNotice(const DeathNotice& _other) = delete; 
	DeathNotice(DeathNotice&& _other) noexcept = delete;
	DeathNotice& operator=(const DeathNotice& _other) = delete;
	DeathNotice& operator=(const DeathNotice&& _other) = delete;

private:
	void TitleBarEvent(GameEngineCollision* _OtherCollision);
	void OkBtnEvent(GameEngineCollision* _OtherCollision);

	GameEngineUIRenderer* BgRenderer_;
	GameEngineCollision* TitleBar_;
	bool Grabbed_;

	GameEngineUIRenderer* OkBtn_;
	GameEngineCollision*  OkBtnCol_;
};

