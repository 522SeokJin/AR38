#include "PreCompile.h"
#include "GameEngineShader.h"

GameEngineShader::GameEngineShader() // default constructer 디폴트 생성자
	: VersionHigh_(5)
	, VersionLow_(0)
	, CodeBlob_(nullptr)
{

}

GameEngineShader::~GameEngineShader() // default destructer 디폴트 소멸자
{
	
}

void GameEngineShader::SetVersion(UINT _VersionHigh, UINT _VersionLow)
{
	VersionHigh_ = _VersionHigh;
	VersionLow_ = _VersionLow;
}

void GameEngineShader::CreateVersion(const std::string& _ShaderType)
{
	Version_ = "";
	Version_ += _ShaderType +"_";
	Version_ += std::to_string(VersionHigh_);
	Version_ += "_";
	Version_ += std::to_string(VersionLow_);
}

void GameEngineShader::SetCode(const std::string& _Code)
{
	Code_ = _Code;
}

void GameEngineShader::SetEntryPoint(const std::string& _EntryPoint)
{
	EntryPoint_ = _EntryPoint;
}