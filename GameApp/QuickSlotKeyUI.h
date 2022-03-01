#pragma once
#include "GameEngine/GameEngineActor.h"

// Ό³Έν : 
class QuickSlotKeyUI : public GameEngineActor
{
public:
	QuickSlotKeyUI();
	~QuickSlotKeyUI();

	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;

protected:
	QuickSlotKeyUI(const QuickSlotKeyUI& _other) = delete; 
	QuickSlotKeyUI(QuickSlotKeyUI&& _other) noexcept = delete;
	QuickSlotKeyUI& operator=(const QuickSlotKeyUI& _other) = delete;
	QuickSlotKeyUI& operator=(const QuickSlotKeyUI&& _other) = delete;

private:

};

