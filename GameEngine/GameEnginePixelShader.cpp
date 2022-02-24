#include "PreCompile.h"
#include "GameEnginePixelShader.h"
#include <GameEngineBase\GameEngineString.h>
#include "GameEngineShaderResHelper.h"

GameEnginePixelShader::GameEnginePixelShader() // default constructer ����Ʈ ������
	: Shader_(nullptr)
	, GameEngineShader(ShaderType::PS)
{

}

GameEnginePixelShader::~GameEnginePixelShader() // default destructer ����Ʈ �Ҹ���
{
	if (nullptr != Shader_)
	{
		Shader_->Release();
		Shader_ = nullptr;
	}
}

bool GameEnginePixelShader::Create(
	const std::string& _ShaderCode,
	const std::string& _EntryPoint,
	UINT _VersionHigh /*= 5*/,
	UINT _VersionLow /*= 0*/
)
{
	SetVersion(_VersionHigh, _VersionLow);
	SetEntryPoint(_EntryPoint);
	SetCode(_ShaderCode);
	CreateVersion("ps");

	return StringCompile();
}

bool GameEnginePixelShader::Load(const std::string& _Path,
	const std::string& _EntryPoint,
	UINT _VersionHigh /*= 5*/,
	UINT _VersionLow /*= 0*/
)
{
	SetVersion(_VersionHigh, _VersionLow);
	SetEntryPoint(_EntryPoint);
	CreateVersion("ps");

	return FileCompile(_Path);
}

bool GameEnginePixelShader::StringCompile()
{
	unsigned int Flag = 0;

#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;
#endif

	// ����� ��ġ�� �Ǽ� ���°��� �����ش�.
	// ��ġ�� �⺻�̰� ��ġ�Ȱ� �ٽ� �ٲ���
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	// ������� ����Ʈ�ڵ� Binary Large Object
	// �������Ҷ� ������ .obj���ϰ��� �ڵ尡 ���´�.
	ID3DBlob* ResultBlob = nullptr;
	ID3DBlob* ErrorBlob = nullptr;


	// D3DCompile()			: ���� ���ڿ��� ����
	// D3DCompileFromFile() : �ؽ�Ʈ���� �о��
	if (S_OK != D3DCompile(
		Code_.c_str(),
		Code_.size(),
		"",
		nullptr,
		nullptr,
		EntryPoint_.c_str(),	// void Function() �� ����Ѵ��ϸ�, "Function"�� �־�����Ѵ�. (�Լ���)
		Version_.c_str(),
		Flag,
		0,
		&ResultBlob,
		&ErrorBlob))
	{
		std::string ErrorText = (char*)ErrorBlob->GetBufferPointer();
		GameEngineDebug::MsgBox(GetName() + " ������ ���� ������ �߻��߽��ϴ�.");
		GameEngineDebug::MsgBox(ErrorText);
		return false;
	}

	CodeBlob_ = ResultBlob;

	if (S_OK != GameEngineDevice::GetDevice()->CreatePixelShader(CodeBlob_->GetBufferPointer(),
		CodeBlob_->GetBufferSize(), nullptr, &Shader_))
	{
		GameEngineDebug::MsgBoxError("���ؽ����̴� ������ �����߽��ϴ�.");
		return false;
	}

	ResCheck();

	return true;
}

bool GameEnginePixelShader::FileCompile(const std::string& _Path)
{
	unsigned int Flag = 0;

#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;
#endif

	// ����� ��ġ�� �Ǽ� ���°��� �����ش�.
	// ��ġ�� �⺻�̰� ��ġ�Ȱ� �ٽ� �ٲ���
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	// ������� ����Ʈ�ڵ� Binary Large Object
	// �������Ҷ� ������ .obj���ϰ��� �ڵ尡 ���´�.
	ID3DBlob* ResultBlob = nullptr;
	ID3DBlob* ErrorBlob = nullptr;

	std::wstring Path;
	GameEngineString::StringToWString(_Path, Path);

	// D3DCompile()			: ���� ���ڿ��� ����
	// D3DCompileFromFile() : �ؽ�Ʈ���� �о��
	if (S_OK != D3DCompileFromFile(
		Path.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,	// ��ο� �ִ� include ���ϵ��� ���Խ����ش�.
		EntryPoint_.c_str(),
		Version_.c_str(),
		Flag,
		0,
		&ResultBlob,
		&ErrorBlob))
	{
		std::string ErrorText = (char*)ErrorBlob->GetBufferPointer();
		GameEngineDebug::MsgBox(GetName() + " ������ ���� ������ �߻��߽��ϴ�.");
		GameEngineDebug::MsgBox(ErrorText);
		return false;
	}

	CodeBlob_ = ResultBlob;

	if (S_OK != GameEngineDevice::GetDevice()->CreatePixelShader(CodeBlob_->GetBufferPointer(),
		CodeBlob_->GetBufferSize(), nullptr, &Shader_))
	{
		GameEngineDebug::MsgBoxError("���ؽ����̴� ������ �����߽��ϴ�.");
		return false;
	}

	ResCheck();

	return true;
}

void GameEnginePixelShader::Setting()
{
	GameEngineDevice::GetContext()->PSSetShader(Shader_, nullptr, 0);
}

void GameEnginePixelShader::SetConstantBuffers(const GameEngineConstantBufferSetting* _Setting)
{
	GameEngineDevice::GetContext()->PSSetConstantBuffers(_Setting->SettingIndex_, 1, &_Setting->Res_->GetBuffer());
}

void GameEnginePixelShader::SetTexture(const GameEngineTextureSetting* _Setting)
{
	GameEngineDevice::GetContext()->PSSetShaderResources(_Setting->SettingIndex_, 1,
		_Setting->Res_->GetShaderResourceView());
}

