#pragma once
#include "GameEngineImageRenderer.h"

// ���� : �ϳ��� ���������� ǥ���Ѵ�.
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
		float _FontSize, float4 _Color = float4::RED, float4 _Pivot = float4::ZERO);

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

	static int UIRendererCount_;
	static GameEngineRenderTarget* FontTarget_;

private:
	void Start() override;

	void Render() override;

};

