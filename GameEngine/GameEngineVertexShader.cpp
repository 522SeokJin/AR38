#include "PreCompile.h"
#include "GameEngineVertexShader.h"
#include "GameEngineDirectXDevice.h"

GameEngineVertexShader::GameEngineVertexShader() // default constructer 디폴트 생성자
	: VersionHigh_(5)
	, VersionLow_(0)
	, CodeBlob_(nullptr)
{

}

GameEngineVertexShader::~GameEngineVertexShader() // default destructer 디폴트 소멸자
{
	if (nullptr != Layout_)
	{
		Layout_->Release();
		Layout_ = nullptr;
	}

	if (nullptr != CodeBlob_)
	{
		CodeBlob_->Release();
		CodeBlob_ = nullptr;
	}
}

bool GameEngineVertexShader::Create(
	const std::string& _ShaderCode,
	const std::string& _EntryPoint,
	UINT _VersionHigh,
	UINT _VersionLow
)
{
	SetVersion(_VersionHigh, _VersionLow);
	SetEntryPoint(_EntryPoint);
	SetCode(_ShaderCode);
	CreateVersion();

	return Compile();
}

void GameEngineVertexShader::SetCode(const std::string& _Code)
{
	Code_ = _Code;
}

void GameEngineVertexShader::SetEntryPoint(const std::string& _EntryPoint)
{
	EntryPoint_ = _EntryPoint;
}

bool GameEngineVertexShader::Compile()
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


	// D3DCompile() -> 직접 문자열을 넣음
	// D3DCompileFromFile() -> 텍스트파일 읽어옴
	if (S_OK != D3DCompile(
		Code_.c_str(),
		Code_.size(),
		"",
		nullptr,
		nullptr,
		EntryPoint_.c_str(),	// void Function() 을 사용한다하면, "Function"을 넣어줘야한다. (함수명)
		Version_.c_str(),
		0,						// Flags1,2 -> Defalut
		0,
		&ResultBlob,
		&ErrorBlob))
	{
		std::string ErrorText = (char*)ErrorBlob->GetBufferPointer();
		GameEngineDebug::MsgBox(ErrorText);
		return false;
	}

	CodeBlob_ = ResultBlob;

	return true;
}

void GameEngineVertexShader::SetVersion(UINT _VersionHigh, UINT _VersionLow)
{
	VersionHigh_ = _VersionHigh;
	VersionLow_ = _VersionLow;
}

void GameEngineVertexShader::CreateVersion()
{
	Version_ = "";
	Version_ += "vs_";
	Version_ += std::to_string(VersionHigh_);
	Version_ += "_";
	Version_ += std::to_string(VersionLow_);
}

void GameEngineVertexShader::AddInputLayout(
	const char* _SemanticName,
	unsigned int _SemanticIndex,
	unsigned int _AlignedByteOffset,
	DXGI_FORMAT _Format,
	unsigned int _InputSlot,
	unsigned int _InstanceDataStepRate,
	D3D11_INPUT_CLASSIFICATION _InputClass
)
{
	SemanticName_.push_back(_SemanticName);

	D3D11_INPUT_ELEMENT_DESC LayoutDesc = { 0, };

	// https://docs.microsoft.com/ko-kr/windows/win32/direct3dhlsl/dx-graphics-hlsl-semantics
	
	// "POSITION"
	LayoutDesc.SemanticName = _SemanticName;
	// 0번 (POSITION 0)
	LayoutDesc.SemanticIndex = _SemanticIndex;
	// 16 -> 16Byte 위치
	LayoutDesc.AlignedByteOffset = _AlignedByteOffset;	// LayOutOffset_?
	// DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT
	LayoutDesc.Format = _Format;
	// 0 -> 아직안씀
	LayoutDesc.InputSlot = _InputSlot;
	// 0 -> 아직안씀
	LayoutDesc.InstanceDataStepRate = _InstanceDataStepRate;
	
	InputLayoutDesc_.push_back(LayoutDesc);

	//struct GameEngineVertex
	//{
	//public:
	//	// 포지션
	//	// 텍스처 비율
	//	float4 Postion1; POSTION 1 0
	//	float4 Postion0; POSTION 0 16
	//  float4 Postion2; POSTION 2 32 
	//	float4 Color; COLOR 0 48
	//}
}

void GameEngineVertexShader::CreateLayout()
{
	//GameEngineDirectXDevice::GetDevice()->CreateInputLayout();
}

void GameEngineVertexShader::LayoutClear()
{
	
	if (nullptr != Layout_)
	{
		Layout_->Release();
	}
	Layout_ = nullptr;

	LayoutOffset_ = 0;
	SemanticName_.clear();
	InputLayoutDesc_.clear();
}
