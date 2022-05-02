#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class SahelLevel : public GameEngineLevel
{
public:
	SahelLevel();
	~SahelLevel();

	void LevelStart() override;
	void LevelUpdate(float _DeltaTime) override;
	void LevelChangeEndEvent(GameEngineLevel* _NextLevel) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

protected:
	SahelLevel(const SahelLevel& _other) = delete; 
	SahelLevel(SahelLevel&& _other) noexcept = delete;
	SahelLevel& operator=(const SahelLevel& _other) = delete;
	SahelLevel& operator=(const SahelLevel&& _other) = delete;

private:

};

