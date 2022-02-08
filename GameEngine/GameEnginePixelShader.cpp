#include "PreCompile.h"
#include "GameEnginePixelShader.h"

GameEnginePixelShader::GameEnginePixelShader() // default constructer ����Ʈ ������
	: Shader_(nullptr)
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

	return Compile();
}

bool GameEnginePixelShader::Compile()
{
	unsigned int Flag = 0;

#ifdef _DEBUG
	Flag = D3D10_SHADER_DEBUG;
#endif

	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	ID3DBlob* ResultBlob = nullptr;
	ID3DBlob* ErrorBlob = nullptr;

	if (S_OK != D3DCompile(
		Code_.c_str(),
		Code_.size(),
		"",
		nullptr,
		nullptr,
		EntryPoint_.c_str(),	
		Version_.c_str(),
		0,						
		0,
		&ResultBlob,
		&ErrorBlob))
	{
		std::string ErrorText = (char*)ErrorBlob->GetBufferPointer();
		GameEngineDebug::MsgBox(ErrorText);
		return false;
	}

	CodeBlob_ = ResultBlob;

	if (S_OK != GameEngineDevice::GetDevice()->CreatePixelShader(CodeBlob_->GetBufferPointer(),
		CodeBlob_->GetBufferSize(), nullptr, &Shader_))
	{
		GameEngineDebug::MsgBoxError("�ȼ����̴� ������ �����߽��ϴ�.");
		return false;
	}

	return true;
}

void GameEnginePixelShader::Setting()
{
	GameEngineDevice::GetContext()->PSSetShader(Shader_, nullptr, 0);
}