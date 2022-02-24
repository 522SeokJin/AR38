#include "PreCompile.h"
#include "GameEnginePixelShader.h"
#include <GameEngineBase\GameEngineString.h>
#include "GameEngineShaderResHelper.h"

GameEnginePixelShader::GameEnginePixelShader() // default constructer 디폴트 생성자
	: Shader_(nullptr)
	, GameEngineShader(ShaderType::PS)
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

	// 행렬이 전치가 되서 들어가는것을 막아준다.
	// 전치가 기본이고 전치된걸 다시 바꿔줌
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	// 결과물의 바이트코드 Binary Large Object
	// 컴파일할때 나오는 .obj파일같은 코드가 나온다.
	ID3DBlob* ResultBlob = nullptr;
	ID3DBlob* ErrorBlob = nullptr;


	// D3DCompile()			: 직접 문자열을 넣음
	// D3DCompileFromFile() : 텍스트파일 읽어옴
	if (S_OK != D3DCompile(
		Code_.c_str(),
		Code_.size(),
		"",
		nullptr,
		nullptr,
		EntryPoint_.c_str(),	// void Function() 을 사용한다하면, "Function"을 넣어줘야한다. (함수명)
		Version_.c_str(),
		Flag,
		0,
		&ResultBlob,
		&ErrorBlob))
	{
		std::string ErrorText = (char*)ErrorBlob->GetBufferPointer();
		GameEngineDebug::MsgBox(GetName() + " 컴파일 도중 에러가 발생했습니다.");
		GameEngineDebug::MsgBox(ErrorText);
		return false;
	}

	CodeBlob_ = ResultBlob;

	if (S_OK != GameEngineDevice::GetDevice()->CreatePixelShader(CodeBlob_->GetBufferPointer(),
		CodeBlob_->GetBufferSize(), nullptr, &Shader_))
	{
		GameEngineDebug::MsgBoxError("버텍스쉐이더 생성에 실패했습니다.");
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

	// 행렬이 전치가 되서 들어가는것을 막아준다.
	// 전치가 기본이고 전치된걸 다시 바꿔줌
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	// 결과물의 바이트코드 Binary Large Object
	// 컴파일할때 나오는 .obj파일같은 코드가 나온다.
	ID3DBlob* ResultBlob = nullptr;
	ID3DBlob* ErrorBlob = nullptr;

	std::wstring Path;
	GameEngineString::StringToWString(_Path, Path);

	// D3DCompile()			: 직접 문자열을 넣음
	// D3DCompileFromFile() : 텍스트파일 읽어옴
	if (S_OK != D3DCompileFromFile(
		Path.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,	// 경로에 있는 include 파일들을 포함시켜준다.
		EntryPoint_.c_str(),
		Version_.c_str(),
		Flag,
		0,
		&ResultBlob,
		&ErrorBlob))
	{
		std::string ErrorText = (char*)ErrorBlob->GetBufferPointer();
		GameEngineDebug::MsgBox(GetName() + " 컴파일 도중 에러가 발생했습니다.");
		GameEngineDebug::MsgBox(ErrorText);
		return false;
	}

	CodeBlob_ = ResultBlob;

	if (S_OK != GameEngineDevice::GetDevice()->CreatePixelShader(CodeBlob_->GetBufferPointer(),
		CodeBlob_->GetBufferSize(), nullptr, &Shader_))
	{
		GameEngineDebug::MsgBoxError("버텍스쉐이더 생성에 실패했습니다.");
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

