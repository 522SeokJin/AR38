#pragma once
#include <GameEngine\GameEngineActor.h>

// Ό³Έν : 
class TopUI : public GameEngineActor
{
private:	// member Var


public:
	// constrcuter destructer
	TopUI();
	~TopUI();

public:
	// delete Function
	TopUI(const TopUI& _other) = delete; 
	TopUI(TopUI&& _other) noexcept = delete;
	TopUI& operator=(const TopUI& _other) = delete;
	TopUI& operator=(const TopUI&& _other) = delete;

private:
	void Start() override;
};

