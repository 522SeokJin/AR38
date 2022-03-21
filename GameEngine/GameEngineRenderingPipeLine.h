#pragma once
#include <GameEngine/GameEngineDevice.h>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineRenderingSettingData.h"
#include "GameEngineShaderResHelper.h"

// 설명 : 렌더링파이프라인을 직접 설정하기위해 만든 클래스
class GameEngineBlend;
class GameEngineShader;
class GameEngineDepthStencil;
class GameEngineConstantBuffer;
class GameEngineVertexBuffer;
class GameEngineVertexShader;
class GameEngineIndexBuffer;
class GameEngineRasterizer;
class GameEnginePixelShader;
class GameEngineRenderingPipeLine : public GameEngineObjectNameBase
{
public:
	GameEngineRenderingPipeLine();
	~GameEngineRenderingPipeLine();

	inline GameEngineVertexShader* GetVertexShader() const
	{
		return VertexShader_;
	}

	inline GameEnginePixelShader* GetPixelShader() const
	{
		return PixelShader_;
	}

	void SetInputAssembler1VertexBufferSetting(const std::string& _Name);
	void SetInputAssembler1InputLayoutSetting(const std::string& _Name);

	void SetVertexShader(const std::string& _Name);

	void SetInputAssembler2IndexBufferSetting(const std::string& _Name);
	void SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY _Topology);

	void SetRasterizer(const std::string& _Name);

	void SetPixelShader(const std::string& _Name);

	void SetOutputMergerBlend(const std::string& _Name);

	void SetOutputMergerDepthStencil(const std::string& _Name);

	void RenderingPipeLineSetting();

	void Rendering();

	void Reset();

protected:
	GameEngineRenderingPipeLine(const GameEngineRenderingPipeLine& _other) = delete;
	GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _other) = delete;
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine& _other) = delete;
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine&& _other) = delete;

private:
	void InputAssembler1();
	void InputAssembler2();
	void VertexShader();
	void Rasterizer();
	void PixelShader();
	void OutputMerger();

	// VertexBuffer 에서 복사해서 받아온다.
	// IA1
	GameEngineVertexBuffer*		VertexBuffer_;
	GameEngineVertexShader*		InputLayoutVertexShader_;
	// VS
	GameEngineVertexShader*		VertexShader_;
	// IA2
	GameEngineIndexBuffer*		IndexBuffer_;
	D3D11_PRIMITIVE_TOPOLOGY	Topology_;
	// RS
	GameEngineRasterizer*		Rasterizer_;
	// PS
	GameEnginePixelShader*		PixelShader_;
	// Blend
	GameEngineBlend*			Blend_;
	// OM
	GameEngineRenderTarget*		RenderTarget_;

	GameEngineDepthStencil*		DepthStencil_;
};

