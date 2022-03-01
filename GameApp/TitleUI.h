#pragma once
#include "GameEngine/GameEngineActor.h"

// ���� : 
class TitleUI : public GameEngineActor
{
public:
	TitleUI();
	~TitleUI();

	virtual void Start() override;
	virtual void Update(float _DeltaTime) override;

protected:
	TitleUI(const TitleUI& _other) = delete; 
	TitleUI(TitleUI&& _other) noexcept = delete;
	TitleUI& operator=(const TitleUI& _other) = delete;
	TitleUI& operator=(const TitleUI&& _other) = delete;

private:
	
};

