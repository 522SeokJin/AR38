#pragma once
#include "GameEngineImageRenderer.h"

// 설명 : 하나의 렌더단위를 표현한다.
class CameraComponent;
class GameEngineLevel;
class GameEngineRenderingPipeLine;
class GameEngineUIRenderer : public GameEngineImageRenderer
{
	friend GameEngineLevel;
	friend CameraComponent;

public:
	GameEngineUIRenderer();
	~GameEngineUIRenderer();

	void SetRenderGroup(int _Order) override;

	void TextSetting(const std::string& _FontName, const std::string& _PrintText, 
		float _FontSize, float4 _Color = float4::RED);

protected:
	GameEngineUIRenderer(const GameEngineUIRenderer& _other) = delete; 
	GameEngineUIRenderer(GameEngineUIRenderer&& _other) noexcept = delete;
	GameEngineUIRenderer& operator=(const GameEngineUIRenderer& _other) = delete;
	GameEngineUIRenderer& operator=(const GameEngineUIRenderer&& _other) = delete;

	std::string FontName_;
	std::string PrintText_;
	float FontSize_;
	float4 FontPivot_;
	float4 Color_;

private:
	void Start() override;

	void Render() override;

};

