#pragma once
#include "GameEngineShader.h"
#include "GameEngineDevice.h"

// 설명 : 
class GameEnginePixelShader : public GameEngineShader
{
private:	// member Var
	ID3D11PixelShader* Shader_;

public:
	GameEnginePixelShader(); // default constructer 디폴트 생성자
	~GameEnginePixelShader(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEnginePixelShader(const GameEnginePixelShader& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEnginePixelShader(GameEnginePixelShader&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEnginePixelShader& operator=(const GameEnginePixelShader& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEnginePixelShader& operator=(const GameEnginePixelShader&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
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

	void Setting();

	void SetConstantBuffers(const GameEngineConstantBufferSetting* _Setting) override;
	void SetSamplers(const GameEngineSamplerSetting* _Setting) override;
	void SetTextures(const GameEngineTextureSetting* _Setting) override;

	void ResetConstantBuffers(const GameEngineConstantBufferSetting* _Setting) override;
	void ResetSamplers(const GameEngineSamplerSetting* _Setting) override;
	void ResetTextures(const GameEngineTextureSetting* _Setting) override;
};

