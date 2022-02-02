#include "PreCompile.h"
#include "GameEngineVertexShader.h"
#include "GameEngineDirectXDevice.h"

GameEngineVertexShader::GameEngineVertexShader() // default constructer ����Ʈ ������
	: VersionHigh_(5)
	, VersionLow_(0)
	, CodeBlob_(nullptr)
{

}

GameEngineVertexShader::~GameEngineVertexShader() // default destructer ����Ʈ �Ҹ���
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

	// ����� ��ġ�� �Ǽ� ���°��� �����ش�.
	// ��ġ�� �⺻�̰� ��ġ�Ȱ� �ٽ� �ٲ���
	Flag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	// ������� ����Ʈ�ڵ� Binary Large Object
	// �������Ҷ� ������ .obj���ϰ��� �ڵ尡 ���´�.
	ID3DBlob* ResultBlob = nullptr;
	ID3DBlob* ErrorBlob = nullptr;


	// D3DCompile() -> ���� ���ڿ��� ����
	// D3DCompileFromFile() -> �ؽ�Ʈ���� �о��
	if (S_OK != D3DCompile(
		Code_.c_str(),
		Code_.size(),
		"",
		nullptr,
		nullptr,
		EntryPoint_.c_str(),	// void Function() �� ����Ѵ��ϸ�, "Function"�� �־�����Ѵ�. (�Լ���)
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
	// 0�� (POSITION 0)
	LayoutDesc.SemanticIndex = _SemanticIndex;
	// 16 -> 16Byte ��ġ
	LayoutDesc.AlignedByteOffset = _AlignedByteOffset;	// LayOutOffset_?
	// DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT
	LayoutDesc.Format = _Format;
	// 0 -> �����Ⱦ�
	LayoutDesc.InputSlot = _InputSlot;
	// 0 -> �����Ⱦ�
	LayoutDesc.InstanceDataStepRate = _InstanceDataStepRate;
	
	InputLayoutDesc_.push_back(LayoutDesc);

	//struct GameEngineVertex
	//{
	//public:
	//	// ������
	//	// �ؽ�ó ����
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
