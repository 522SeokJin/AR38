#pragma once
#include "GameEngineShader.h"
#include "GameEngineDevice.h"

// �з� : 
// �뵵 : 
// ���� : 
class GameEnginePixelShader : public GameEngineShader
{
private:	// member Var
	ID3D11PixelShader* Shader_;

public:
	GameEnginePixelShader(); // default constructer ����Ʈ ������
	~GameEnginePixelShader(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEnginePixelShader(const GameEnginePixelShader& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEnginePixelShader(GameEnginePixelShader&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEnginePixelShader& operator=(const GameEnginePixelShader& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEnginePixelShader& operator=(const GameEnginePixelShader&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

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

	// ������ ���׿� ������ ���ٸ� �߰��� ���ĵ� �ٷ� ������ �ȴ�.
	bool StringCompile();

	bool FileCompile(const std::string& _Path);

public:
	void Setting();
};

