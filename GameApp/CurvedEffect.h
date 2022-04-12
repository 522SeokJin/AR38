#pragma once
#include <GameEngine/GameEnginePostProcessRender.h>

// Ό³Έν : 
class CurvedEffect : public GameEnginePostProcessRender
{
public:
	CurvedEffect();
	~CurvedEffect();

protected:
	CurvedEffect(const CurvedEffect& _other) = delete; 
	CurvedEffect(CurvedEffect&& _other) noexcept = delete;
	CurvedEffect& operator=(const CurvedEffect& _other) = delete;
	CurvedEffect& operator=(const CurvedEffect&& _other) = delete;

	void Effect(float _DeltaTime) override;
	void Initialize() override;

private:

};

