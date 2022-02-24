#pragma once
#include "GameEngineDevice.h"

enum class ShaderType
{
	VS,
	PS,
	MAX
};


// Ό³Έν : 
class GameEngineConstantBuffer;
class GameEngineTexture;
class GameEngineSampler;
class GameEngineConstantBufferSetting;
class GameEngineTextureSetting;
class GameEngineSamplerSetting;
class GameEngineShader : public GameEngineObjectNameBase
{
protected:	// member Var
	ShaderType	Type_;

	UINT		VersionHigh_;
	UINT		VersionLow_;
	std::string Version_;

	ID3DBlob*	CodeBlob_;

	std::string	EntryPoint_;
	std::string Code_;

public:
	// constrcuter destructer
	GameEngineShader(ShaderType _Type);
	virtual ~GameEngineShader() = 0;

public:
	// delete Function
	GameEngineShader(const GameEngineShader& _other) = delete;
	GameEngineShader(GameEngineShader&& _other) noexcept = delete; 
	GameEngineShader& operator=(const GameEngineShader& _other) = delete; 
	GameEngineShader& operator=(const GameEngineShader&& _other) = delete;

protected:
	void SetVersion(UINT _VersionHigh, UINT _VersionLow);
	void CreateVersion(const std::string& _ShaderType);
	void SetCode(const std::string& _Code);
	void SetEntryPoint(const std::string& _EntryPoint);

	/// <summary>
	/////////////////////////	Resource 
	/// </summary>

	void ResCheck();	// Resource Check

private:
	std::map<UINT, GameEngineConstantBuffer*> ConstantBuffers_;
	
	std::map<UINT, GameEngineSampler*> Samplers_;

	std::map<UINT, std::string> Textures_;

public:
	std::map<UINT, GameEngineConstantBuffer*>&	GetConstantBuffers() { return ConstantBuffers_; }
	std::map<UINT, GameEngineSampler*>&			GetSamplers() { return Samplers_; }
	std::map<UINT, std::string>&				GetTextures() { return Textures_; }

	virtual void SetConstantBuffers(const GameEngineConstantBufferSetting* _Setting) = 0;
	virtual void SetSamplers(const GameEngineSamplerSetting* _Setting) = 0;
	virtual void SetTextures(const GameEngineTextureSetting* _Setting) = 0;

	virtual void ResetConstantBuffers(const GameEngineConstantBufferSetting* _Setting) = 0;
	virtual void ResetSamplers(const GameEngineSamplerSetting* _Setting) = 0;
	virtual void ResetTextures(const GameEngineTextureSetting* _Setting) = 0;

};

