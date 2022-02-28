#pragma once
#include "GameEngineShader.h"
#include "GameEngineDevice.h"

// ���� : 
class GameEnginePixelShader : public GameEngineShader
{
public:
	GameEnginePixelShader(); 
	~GameEnginePixelShader();

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

	void Setting();

	void SetConstantBuffers(const GameEngineConstantBufferSetting* _Setting) override;
	void SetSamplers(const GameEngineSamplerSetting* _Setting) override;
	void SetTextures(const GameEngineTextureSetting* _Setting) override;

	void ResetConstantBuffers(const GameEngineConstantBufferSetting* _Setting) override;
	void ResetSamplers(const GameEngineSamplerSetting* _Setting) override;
	void ResetTextures(const GameEngineTextureSetting* _Setting) override;

protected:
	GameEnginePixelShader(const GameEnginePixelShader& _other) = delete; 
	GameEnginePixelShader(GameEnginePixelShader&& _other) noexcept = delete; 
	GameEnginePixelShader& operator=(const GameEnginePixelShader& _other) = delete;
	GameEnginePixelShader& operator=(const GameEnginePixelShader&& _other) = delete;

private:
	ID3D11PixelShader* Shader_;
};

