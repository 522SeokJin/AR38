#pragma once
#include "GameEngineGUI.h"
#include "GameEngineRenderTarget.h"

// Ό³Έν : 
class GameEngineImageShotWindow : public GameEngineGUIWindow
{
public:
	GameEngineImageShotWindow();
	~GameEngineImageShotWindow();

	void SetView(ID3D11ShaderResourceView* _View, float4 _Size)
	{
		Size_ = _Size;
		View_ = _View;
	}

protected:
	GameEngineImageShotWindow(const GameEngineImageShotWindow& _other) = delete; 
	GameEngineImageShotWindow(GameEngineImageShotWindow&& _other) noexcept = delete;
	GameEngineImageShotWindow& operator=(const GameEngineImageShotWindow& _other) = delete;
	GameEngineImageShotWindow& operator=(const GameEngineImageShotWindow&& _other) = delete;

	void Start() override;

	void OnGUI() override;

private:
	ID3D11ShaderResourceView* View_;
	float4 Size_;
};

