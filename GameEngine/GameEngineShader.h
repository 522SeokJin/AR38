#pragma once
#include "GameEngineDevice.h"

// �з� : 
// �뵵 : 
// ���� : 
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
	GameEngineShader(); // default constructer ����Ʈ ������
	virtual ~GameEngineShader() = 0; // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineShader(const GameEngineShader& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineShader(GameEngineShader&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineShader& operator=(const GameEngineShader& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineShader& operator=(const GameEngineShader&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

protected:
	void SetVersion(UINT _VersionHigh, UINT _VersionLow);
	void CreateVersion(const std::string& _ShaderType);
	void SetCode(const std::string& _Code);
	void SetEntryPoint(const std::string& _EntryPoint);

};

