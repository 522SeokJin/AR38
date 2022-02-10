#include "PreCompile.h"
#include "GameEngineVertexShader.h"
#include "GameEngineDevice.h"
#include <GameEngineBase/GameEngineString.h>

GameEngineVertexShader::GameEngineVertexShader() // default constructer 디폴트 생성자
	: Shader_(nullptr)
	, Layout_(nullptr)
	, LayoutOffset_(0)
{

}

GameEngineVertexShader::~GameEngineVertexShader() // default destructer 디폴트 소멸자
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

	if (S_OK != GameEngineDevice::GetDevice()->CreateVertexShader(CodeBlob_->GetBufferPointer(),
		CodeBlob_->GetBufferSize(), nullptr, &Shader_))
	{
		GameEngineDebug::MsgBoxError("버텍스쉐이더 생성에 실패했습니다.");
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

	if (S_OK != GameEngineDevice::GetDevice()->CreateVertexShader(CodeBlob_->GetBufferPointer(),
		CodeBlob_->GetBufferSize(), nullptr, &Shader_))
	{
		GameEngineDebug::MsgBoxError("버텍스쉐이더 생성에 실패했습니다.");
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
	// 0번 (POSITION 0)
	LayoutDesc.SemanticIndex = _SemanticIndex;
	// 16 -> 16Byte 위치
	LayoutDesc.AlignedByteOffset = LayoutOffset_;	// _AlignedByteOffset
	// DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT
	LayoutDesc.Format = _Format;
	// 0 -> 아직안씀
	LayoutDesc.InputSlot = _InputSlot;
	// 0 -> 아직안씀
	LayoutDesc.InstanceDataStepRate = _InstanceDataStepRate;
	
	LayoutOffset_ += _AlignedByteOffset;

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
		GameEngineDebug::MsgBoxError("인풋레이아웃 생성에 실패했습니다.");
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

	// 내가 쉐이더에서 사용한 변수, 함수, 인자들 그 이외의 상수버퍼 등의
	// 모든 정보를 알고있다.
	// ex) 쉐이더에서 행렬을 1개 사용했다.
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
		GameEngineDebug::MsgBoxError("쉐이더 컴파일 정보를 얻어오지 못했습니다.");
	}

	D3D11_SHADER_DESC Info;

	CompileInfo->GetDesc(&Info);

	std::string Name = "";
	int PrevIndex = 0;

	// InputParameters : VertexShader에 들어오는 InputParameter의 갯수
	// CustomVertex와 서로 순서가 같아야된다. POSITION 0, POSITION 1, COLOR 0 ...
	for (unsigned int i = 0; i < Info.InputParameters; i++)
	{
		D3D11_SIGNATURE_PARAMETER_DESC Input = { 0, };
		CompileInfo->GetInputParameterDesc(i, &Input);

		DXGI_FORMAT Format = DXGI_FORMAT::DXGI_FORMAT_UNKNOWN;

		// 타입이 정수인지 실수인지 부호가 있는지 없는지
		D3D_REGISTER_COMPONENT_TYPE Reg = Input.ComponentType;

		// D3D_REGISTER_COMPONENT_TYPE
		// 그래픽카드에는 데이터가 항상 4바이트로 들어간다.
		// 그래픽카드의 버퍼에 데이터를 넣어줄때
		// 쉐이더는 여기에 있는 형식으로밖에 이해하지 못한다. 

		// float4
		// 1 1 1 1 -> 15
		
		// float3
		// 0 1 1 1 -> 7

		unsigned int ParameterSize = 0;

		// Format을 지정
		switch (Input.Mask)
		{
			// 1개짜리
		case 1:
			ParameterSize = 4;
			switch (Reg)
			{
			case D3D_REGISTER_COMPONENT_UNKNOWN:
				break;
			case D3D_REGISTER_COMPONENT_UINT32:
				// unsigned int형 정보라는 뜻
				Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
				break;
			case D3D_REGISTER_COMPONENT_SINT32:
				Format = DXGI_FORMAT::DXGI_FORMAT_R32_SINT;
				// int형 정보라는 뜻
				break;
			case D3D_REGISTER_COMPONENT_FLOAT32:
				Format = DXGI_FORMAT::DXGI_FORMAT_R32_FLOAT;
				// float형 정보라는 뜻
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
				// unsigned int형 정보라는 뜻
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32_UINT;
				break;
			case D3D_REGISTER_COMPONENT_SINT32:
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32_SINT;
				// int형 정보라는 뜻
				break;
			case D3D_REGISTER_COMPONENT_FLOAT32:
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
				// float형 정보라는 뜻
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
				// unsigned int형 정보라는 뜻
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_UINT;
				break;
			case D3D_REGISTER_COMPONENT_SINT32:
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_SINT;
				// int형 정보라는 뜻
				break;
			case D3D_REGISTER_COMPONENT_FLOAT32:
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
				// float형 정보라는 뜻
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
				// unsigned int형 정보라는 뜻
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_UINT;
				break;
			case D3D_REGISTER_COMPONENT_SINT32:
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_SINT;
				// int형 정보라는 뜻
				break;
			case D3D_REGISTER_COMPONENT_FLOAT32:
				Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
				// float형 정보라는 뜻
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
					GameEngineDebug::MsgBoxError("시멘틱의 인덱스 순서가 잘못되었습니다. 오름차순이 아닙니다.");
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
			GameEngineDebug::MsgBoxError("쉐이더 인풋 파라미터 타입이 정상적이지 않습니다.");
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
		GameEngineDebug::MsgBoxError("쉐이더 인풋 파라미터가 존재하지않습니다.");
	}

	GameEngineDevice::GetContext()->IASetInputLayout(Layout_);
}

void GameEngineVertexShader::Setting()
{
	GameEngineDevice::GetContext()->VSSetShader(Shader_, nullptr, 0);
}
