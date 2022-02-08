#pragma once
#include "GameEngineDevice.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineShader : public GameEngineObjectNameBase
{
protected:	// member Var
	UINT		VersionHigh_;
	UINT		VersionLow_;
	std::string Version_;

	ID3DBlob* CodeBlob_;

	std::string	EntryPoint_;
	std::string Code_;


public:
	GameEngineShader(); // default constructer 디폴트 생성자
	virtual ~GameEngineShader() = 0; // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineShader(const GameEngineShader& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineShader(GameEngineShader&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineShader& operator=(const GameEngineShader& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineShader& operator=(const GameEngineShader&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

protected:
	void SetVersion(UINT _VersionHigh, UINT _VersionLow);
	void CreateVersion(const std::string& _ShaderType);
	void SetCode(const std::string& _Code);
	void SetEntryPoint(const std::string& _EntryPoint);

};

