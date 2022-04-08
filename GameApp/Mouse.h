#pragma once
#include <GameEngine/MouseActor.h>

// Ό³Έν : 
class Mouse : public MouseActor
{
public:
	Mouse();
	~Mouse();

protected:
	Mouse(const Mouse& _other) = delete; 
	Mouse(Mouse&& _other) noexcept = delete;
	Mouse& operator=(const Mouse& _other) = delete;
	Mouse& operator=(const Mouse&& _other) = delete;

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	void ButtonEvent(GameEngineCollision* _OtherCollision);
	void NPCEvent(GameEngineCollision* _OtherCollision);

	GameEngineCollision* Collision_;
};

