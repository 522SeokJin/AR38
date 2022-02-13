#pragma once
#include "GameEngineDevice.h"
#include "GameEngineConstantBuffer.h"


enum class ShaderType
{
	VS,
	PS,
	MAX
};


// Ό³Έν : 
class GameEngineConstantBufferSetting;
class GameEngineShader : public GameEngineObjectNameBase
{
protected:	// member Var
	ShaderType Type_;

	UINT		VersionHigh_;
	UINT		VersionLow_;
	std::string Version_;

	ID3DBlob* CodeBlob_;

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

	void ResCheck();	// Resource Check, GameEngineConstantBuffer Create

	///////////////////////////////////			ConstantBuffer
private:
	std::map<UINT, GameEngineConstantBuffer*> ConstantBuffers_;

public:
	std::map<UINT, GameEngineConstantBuffer*>& GetConstantBuffers()
	{
		return ConstantBuffers_;
	}

	virtual void SetConstantBuffers(const GameEngineConstantBufferSetting* _Setting) = 0;
};

