#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν : 
class QuickSlotUI : public GameEngineActor
{
public:
	QuickSlotUI();
	~QuickSlotUI();

	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;

protected:
	QuickSlotUI(const QuickSlotUI& _other) = delete; 
	QuickSlotUI(QuickSlotUI&& _other) noexcept = delete;
	QuickSlotUI& operator=(const QuickSlotUI& _other) = delete;
	QuickSlotUI& operator=(const QuickSlotUI&& _other) = delete;

private:

};

