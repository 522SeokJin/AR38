#include "PreCompile.h"
#include "GameEnginePixelShader.h"

GameEnginePixelShader::GameEnginePixelShader() // default constructer 디폴트 생성자
	: Shader_(nullptr)
{

}

GameEnginePixelShader::~GameEnginePixelShader() // default destructer 디폴트 소멸자
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
		GameEngineDebug::MsgBoxError("픽셀쉐이더 생성에 실패했습니다.");
		return false;
	}

	return true;
}

void GameEnginePixelShader::Setting()
{
	GameEngineDevice::GetContext()->PSSetShader(Shader_, nullptr, 0);
}