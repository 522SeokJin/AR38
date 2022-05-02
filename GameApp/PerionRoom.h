#pragma once
#include "Map.h"

// Ό³Έν : 
class PerionRoom : public Map
{
public:
	PerionRoom();
	~PerionRoom();

	void Start() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

	GameEngineImageRenderer* GetPixelCollide()
	{
		return PixelCollide_;
	}

protected:
	PerionRoom(const PerionRoom& _other) = delete; 
	PerionRoom(PerionRoom&& _other) noexcept = delete;
	PerionRoom& operator=(const PerionRoom& _other) = delete;
	PerionRoom& operator=(const PerionRoom&& _other) = delete;

private:
	GameEngineImageRenderer* PixelCollide_;
};

