#pragma once
#include "GameEngineGUI.h"
#include "GameEngineRenderTarget.h"

// Ό³Έν : 
class GameEngineRenderWindow : public GameEngineGUIWindow
{
	struct RenderTargetDrawData
	{
	public:
		std::string Name_;
		GameEngineRenderTarget* Target_;
		float4 Size_;
	};
public:
	GameEngineRenderWindow();
	~GameEngineRenderWindow();

	void ClaerRenderTarget()
	{
		DrawRenderTarget_.clear();
	}

	void PushRenderTarget(std::string _Name, GameEngineRenderTarget* _RenderTarget, float4 Size_)
	{
		DrawRenderTarget_.push_back({ _Name, _RenderTarget, Size_, false });
	}

protected:
	GameEngineRenderWindow(const GameEngineRenderWindow& _other) = delete; 
	GameEngineRenderWindow(GameEngineRenderWindow&& _other) noexcept = delete;
	GameEngineRenderWindow& operator=(const GameEngineRenderWindow& _other) = delete;
	GameEngineRenderWindow& operator=(const GameEngineRenderWindow&& _other) = delete;

	void OnGUI() override;

private:
	std::vector<RenderTargetDrawData> DrawRenderTarget_;
};

