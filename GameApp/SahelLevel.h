#pragma once
#include <GameEngine/GameEngineLevel.h>

// Ό³Έν : 
class SahelLevel : public GameEngineLevel
{
public:
	SahelLevel();
	~SahelLevel();

	virtual void LevelStart() override;
	virtual void LevelUpdate(float _DeltaTime) override;
	virtual void LevelChangeEndEvent() override;
	virtual void LevelChangeStartEvent() override;

protected:
	SahelLevel(const SahelLevel& _other) = delete; 
	SahelLevel(SahelLevel&& _other) noexcept = delete;
	SahelLevel& operator=(const SahelLevel& _other) = delete;
	SahelLevel& operator=(const SahelLevel&& _other) = delete;

private:

};

