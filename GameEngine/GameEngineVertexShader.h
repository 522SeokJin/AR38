#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"
#include "GameEngineShader.h"

// 설명 : 정점의 정보값을 변화시켜서, 물체를 특별한 위치로 옮기거나, 텍스처를 바꾸거나, 색상을 바꾸는 등의 일을 한다.
class GameEngineVertexShader : public GameEngineShader
{
public:
	GameEngineVertexShader(); 
	~GameEngineVertexShader();

	bool Create(
		const std::string& _ShaderCode,
		const std::string& _EntryPoint,
		UINT _VersionHigh = 5,
		UINT _VersionLow = 0
	);

	bool Load(const std::string& _Path,
		const std::string& _EntryPoint,
		UINT _VersionHigh = 5,
		UINT _VersionLow = 0
	);

	// 수정한 사항에 에러가 없다면 중간에 고쳐도 바로 적용이 된다.
	bool StringCompile();

	bool FileCompile(const std::string& _Path);

	void SetConstantBuffers(const GameEngineConstantBufferSetting* _Setting) override; 
	void SetSamplers(const GameEngineSamplerSetting* _Setting) override;
	void SetTextures(const GameEngineTextureSetting* _Setting) override;

	void ResetConstantBuffers(const GameEngineConstantBufferSetting* _Setting) override;
	void ResetSamplers(const GameEngineSamplerSetting* _Setting) override;
	void ResetTextures(const GameEngineTextureSetting* _Setting) override;

protected:
	GameEngineVertexShader(const GameEngineVertexShader& _other) = delete;
	GameEngineVertexShader(GameEngineVertexShader&& _other) = delete;
	GameEngineVertexShader& operator=(const GameEngineVertexShader& _other) = delete;
	GameEngineVertexShader& operator=(const GameEngineVertexShader&& _other) = delete;

private:
	ID3D11VertexShader* Shader_;

	/// <summary>
	/// ////////////////////////////// InputLayout Settting
	/// </summary>
	// CustomVertex의 순서를 정해준다.

public:
	void InputLayoutSetting();
	void Setting();

private:
	void AddInputLayout(
		const char* _SemanticName,
		unsigned int _SemanticIndex,
		unsigned int _AlignedByteOffset,
		DXGI_FORMAT _Format,
		unsigned int _InputSlot,
		unsigned int _InstanceDataStepRate,
		D3D11_INPUT_CLASSIFICATION _InputClass
	);

	void CreateLayout();

	void LayoutCheck();

	void LayoutClear();

	ID3D11InputLayout* Layout_;
	unsigned int							LayoutOffset_; // Current Offset Position
	std::vector<std::string>				SemanticName_;
	std::vector<D3D11_INPUT_ELEMENT_DESC>	InputLayoutDesc_;
};

