#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
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
public:
	GameEngineShader(ShaderType _Type);
	virtual ~GameEngineShader() = 0;

	unsigned int GetTypeIndex()
	{
		return static_cast<unsigned int>(Type_);
	}

	std::string& GetPath()
	{
		return Path_;
	}

	void SetPath(const std::string& _Path)
	{
		Path_ = _Path;
	}

protected:
	GameEngineShader(const GameEngineShader& _other) = delete;
	GameEngineShader(GameEngineShader&& _other) noexcept = delete;
	GameEngineShader& operator=(const GameEngineShader& _other) = delete;
	GameEngineShader& operator=(const GameEngineShader&& _other) = delete;

	void SetVersion(UINT _VersionHigh, UINT _VersionLow);
	void CreateVersion(const std::string& _ShaderType);
	void SetCode(const std::string& _Code);
	void SetEntryPoint(const std::string& _EntryPoint);

	ShaderType	Type_;

	UINT		VersionHigh_;
	UINT		VersionLow_;
	std::string Version_;

	ID3DBlob*	CodeBlob_;

	std::string	EntryPoint_;
	std::string Code_;

	std::string	Path_;

	/// <summary>
	/////////////////////////	Resource 
	/// </summary>
public:
	void ResCheck();	// Resource Check

	virtual void SetConstantBuffers(const GameEngineConstantBufferSetting* _Setting) = 0;
	virtual void SetSamplers(const GameEngineSamplerSetting* _Setting) = 0;
	virtual void SetTextures(const GameEngineTextureSetting* _Setting) = 0;

	virtual void ResetConstantBuffers(const GameEngineConstantBufferSetting* _Setting) = 0;
	virtual void ResetSamplers(const GameEngineSamplerSetting* _Setting) = 0;
	virtual void ResetTextures(const GameEngineTextureSetting* _Setting) = 0;

	std::map<UINT, GameEngineConstantBuffer*>&	GetConstantBuffers() { return ConstantBuffers_; }
	std::map<UINT, GameEngineSampler*>&			GetSamplers() { return Samplers_; }
	std::map<UINT, std::string>&				GetTextures() { return Textures_; }

private:
	std::map<UINT, GameEngineConstantBuffer*>	ConstantBuffers_;
	std::map<UINT, GameEngineSampler*>			Samplers_;
	std::map<UINT, std::string>					Textures_;

};

