#include "PreCompile.h"
#include "GameEngineVertexShader.h"
#include "GameEngineDevice.h"
#include <GameEngineBase/GameEngineString.h>

GameEngineVertexShader::GameEngineVertexShader() // default constructer ����Ʈ ������
	: Shader_(nullptr)
	, Layout_(nullptr)
	, LayoutOffset_(0)
{

}

GameEngineVertexShader::~GameEngineVertexShader() // default destructer ����Ʈ �Ҹ���
{
	if (nullptr != Layout_)
	{
		Layout_->Release();
		Layout_ = nullptr;
	}

	if (nullptr != Shader_)
	{
		Shader_->Release();
		Shader_ = nullptr;
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
	UINT _VersionHigh /*= 5*/,
	UINT _VersionLow /*= 0*/
)
{
	SetVersion(_VersionHigh, _VersionLow);
	SetEntryPoint(_EntryPoint);
	SetCode(_ShaderCode);
	CreateVersion("vs");

	return StringCompile();
}

bool GameEngineVertexShader::Load(const std::string& _Path,
	const std::string& _EntryPoint, 
	UINT _VersionHigh /*= 5*/,
	UINT _VersionLow /*= 0*/
)
{
	SetVersion(_VersionHigh, _VersionLow);
	SetEntryPoint(_EntryPoint);
	CreateVersion("vs");

	return FileCompile(_Path);
}

bool GameEngineVertexShader::StringCompile()
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

	if (S_OK != GameEngineDevice::GetDevice()->CreateVertexShader(CodeBlob_->GetBufferPointer(),
		CodeBlob_->GetBufferSize(), nullptr, &Shader_))
	{
		GameEngineDebug::MsgBoxError("���ؽ����̴� ������ �����߽��ϴ�.");
		return false;
	}

	LayoutCheck();
	ResCheck();

	return true;
}

bool GameEngineVertexShader::FileCompile(const std::string& _Path)
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

	if (S_OK != GameEngineDevice::GetDevice()->CreateVertexShader(CodeBlob_->GetBufferPointer(),
		CodeBlob_->GetBufferSize(), nullptr, &Shader_))
	{
		GameEngineDebug::MsgBoxError("���ؽ����̴� ������ �����߽��ϴ�.");
		return false;
	}

	LayoutCheck();
	ResCheck();

	return true;
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
	LayoutDesc.AlignedByteOffset = LayoutOffset_;	// _AlignedByteOffset
	// DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT
	LayoutDesc.Format = _Format;
	// 0 -> �����Ⱦ�
	LayoutDesc.InputSlot = _InputSlot;
	// 0 -> �����Ⱦ�
	LayoutDesc.InstanceDataStepRate = _InstanceDataStepRate;
	
	LayoutOffset_ += _AlignedByteOffset;

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
	if (S_OK != GameEngineDevice::GetDevice()->CreateInputLayout
	(
		&InputLayoutDesc_[0],
		static_cast<unsigned int>(InputLayoutDesc_.size()),
		CodeBlob_->GetBufferPointer(),
		CodeBlob_->GetBufferSize(),
		&Layout_
	)
	)
	{
		GameEngineDebug::MsgBoxError("��ǲ���̾ƿ� ������ �����߽��ϴ�.");
		return;
	}
}

void GameEngineVertexShader::LayoutCheck()
{
	LayoutClear();

	if (nullptr == CodeBlob_)
	{
		return;
	}

	// ���� ���̴����� ����� ����, �Լ�, ���ڵ� �� �̿��� ������� ����
	// ��� ������ �˰��ִ�.
	// ex) ���̴����� ����� 1�� ����ߴ�.
	ID3D11ShaderReflection* CompileInfo;

	if (S_OK != D3DReflect
	(
		CodeBlob_->GetBufferPointer(),
		CodeBlob_->GetBufferSize(),
		IID_ID3D11ShaderReflection,
		reinterpret_cast<void**>(&CompileInfo)
	)
	)
	{
		GameEngineDebug::MsgBoxError("���̴� ������ ������ ������ ���߽��ϴ�.");
	}

	D3D11_SHADER_DESC Info;

	CompileInfo->GetDesc(&Info);

	std::string Name = "";
	int PrevIndex = 0;

	// InputParameters : VertexShader�� ������ InputParameter�� ����
	// CustomVertex�� ���� ������ ���ƾߵȴ�. POSITION 0, POSITION 1, COLOR 0 ...
	for (unsigned int i = 0; i < Info.InputParameters; i++)
	{
		D3D11_SIGNATURE_PARAMETER_DESC Input = { 0, };
		CompileInfo->GetInputParameterDesc(i, &Input);

		DXGI_FORMAT Format = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;

		// Ÿ���� �������� �Ǽ����� ��ȣ�� �ִ��� ������
		D3D_REGISTER_COMPONENT_TYPE Reg = Input.ComponentType;

		// D3D_REGISTER_COMPONENT_TYPE
		// �׷���ī�忡�� �����Ͱ� �׻� 4����Ʈ�� ����.
		// �׷���ī���� ���ۿ� �����͸� �־��ٶ�
		// ���̴��� ���⿡ �ִ� �������ιۿ� �������� ���Ѵ�. 

		// float4
		// 1 1 1 1 -> 15
		
		// float3
		// 0 1 1 1 -> 7

		unsigned int ParameterSize = 0;

		// Format�� ����
		switch (Input.Mask)
		{
			// 1��¥��
		case 1:
			ParameterSize = 4;
			switch (Reg)
			{
			case D3D_REGISTER_COMPONENT_UNKNOWN:
				break;
			case D3D_REGISTER_COMPONENT_UINT32:
				// unsigned int�� ������� ��
				Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
				break;
			case D3D_REGISTER_COMPONENT_SINT32:
				Format = DXGI_FORMAT::DXGI_FORMAT_R32_SINT;
				// int�� ������� ��
				break;
			case D3D_REGISTER_COMPONENT_FLOAT32:
				Format = DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
				// float�� ������� ��
				break;
			default:
				break;
			}
			break;
		case 3:
			ParameterSize = 8;
			switch (Reg)
			{
			case D3D_REGISTER_COMPONENT_UNKNOWN:
				break;
			case D3D_REGISTER_COMPONENT_UINT32:
				// unsigned int�� ������� ��
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32_UINT;
				break;
			case D3D_REGISTER_COMPONENT_SINT32:
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32_SINT;
				// int�� ������� ��
				break;
			case D3D_REGISTER_COMPONENT_FLOAT32:
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
				// float�� ������� ��
				break;
			default:
				break;
			}
			break;
		case 7:
			ParameterSize = 12;
			switch (Reg)
			{
			case D3D_REGISTER_COMPONENT_UNKNOWN:
				break;
			case D3D_REGISTER_COMPONENT_UINT32:
				// unsigned int�� ������� ��
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_UINT;
				break;
			case D3D_REGISTER_COMPONENT_SINT32:
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_SINT;
				// int�� ������� ��
				break;
			case D3D_REGISTER_COMPONENT_FLOAT32:
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
				// float�� ������� ��
				break;
			default:
				break;
			}
			break;
		case 15:
			ParameterSize = 16;
			switch (Reg)
			{
			case D3D_REGISTER_COMPONENT_UNKNOWN:
				break;
			case D3D_REGISTER_COMPONENT_UINT32:
				// unsigned int�� ������� ��
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_UINT;
				break;
			case D3D_REGISTER_COMPONENT_SINT32:
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_SINT;
				// int�� ������� ��
				break;
			case D3D_REGISTER_COMPONENT_FLOAT32:
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
				// float�� ������� ��
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}

		std::string NextName = Input.SemanticName;

		if (Name == "")
		{
			Name = NextName;
			++PrevIndex;
		}
		else
		{
			if (Name == NextName)
			{
				if (PrevIndex != Input.SemanticIndex)
				{
					GameEngineDebug::MsgBoxError("�ø�ƽ�� �ε��� ������ �߸��Ǿ����ϴ�. ���������� �ƴմϴ�.");
					return;
				}

				++PrevIndex;
			}
			else
			{
				Name = NextName;
				PrevIndex = 0;
			}
		}

		if (DXGI_FORMAT::DXGI_FORMAT_UNKNOWN == Format)
		{
			GameEngineDebug::MsgBoxError("���̴� ��ǲ �Ķ���� Ÿ���� ���������� �ʽ��ϴ�.");
		}

		AddInputLayout(Input.SemanticName, Input.SemanticIndex, ParameterSize ,Format, 0, 0,
			D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);
	}

	CreateLayout();
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

void GameEngineVertexShader::InputLayoutSetting()
{
	if (nullptr == Layout_)
	{
		GameEngineDebug::MsgBoxError("���̴� ��ǲ �Ķ���Ͱ� ���������ʽ��ϴ�.");
	}

	GameEngineDevice::GetContext()->IASetInputLayout(Layout_);
}

void GameEngineVertexShader::Setting()
{
	GameEngineDevice::GetContext()->VSSetShader(Shader_, nullptr, 0);
}
