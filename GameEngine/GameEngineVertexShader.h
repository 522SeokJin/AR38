#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"
#include "GameEngineShader.h"

// ���� : ������ �������� ��ȭ���Ѽ�, ��ü�� Ư���� ��ġ�� �ű�ų�, �ؽ�ó�� �ٲٰų�, ������ �ٲٴ� ���� ���� �Ѵ�.
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

	// ������ ���׿� ������ ���ٸ� �߰��� ���ĵ� �ٷ� ������ �ȴ�.
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
	// CustomVertex�� ������ �����ش�.

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

