#include "PreCompile.h"
#include "GameEngineShader.h"
#include "GameEngineResourcesManager.h"

GameEngineShader::GameEngineShader(ShaderType _Type)
	: Type_(_Type)
	, VersionHigh_(5)
	, VersionLow_(0)
	, CodeBlob_(nullptr)
{

}

GameEngineShader::~GameEngineShader()
{
	
}

void GameEngineShader::SetVersion(UINT _VersionHigh, UINT _VersionLow)
{
	VersionHigh_ = _VersionHigh;
	VersionLow_ = _VersionLow;
}

void GameEngineShader::CreateVersion(const std::string& _ShaderType)
{
	Version_ = "";
	Version_ += _ShaderType +"_";
	Version_ += std::to_string(VersionHigh_);
	Version_ += "_";
	Version_ += std::to_string(VersionLow_);
}

void GameEngineShader::SetCode(const std::string& _Code)
{
	Code_ = _Code;
}

void GameEngineShader::SetEntryPoint(const std::string& _EntryPoint)
{
	EntryPoint_ = _EntryPoint;
}

void GameEngineShader::ResCheck()
{
	if (nullptr == CodeBlob_)
	{
		return;
	}

	// 내가 쉐이더에서 사용한 변수, 함수, 인자들 그 이외의 상수버퍼 등의
	// 모든 정보를 알고있다.
	// ex) 쉐이더에서 행렬을 1개 사용했다.
	ID3D11ShaderReflection* CompileInfo = nullptr;

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

	D3D11_SHADER_INPUT_BIND_DESC ResInfo;

	for (UINT i = 0; i < Info.BoundResources; i++)
	{
		CompileInfo->GetResourceBindingDesc(i, &ResInfo);

		// LPCSTR                      Name;           // Name of the resource
		// D3D_SHADER_INPUT_TYPE       Type;           // Type of resource (e.g. texture, cbuffer, etc.)
		// UINT                        BindPoint;      // Starting bind point
		// UINT                        BindCount;      // Number of contiguous bind points (for arrays)
		// UINT                        uFlags;         // Input binding flags
		// D3D_RESOURCE_RETURN_TYPE    ReturnType;     // Return type (if texture)
		// D3D_SRV_DIMENSION           Dimension;      // Dimension (if texture)	// 3차원 텍스처
		// UINT                        NumSamples;     // Number of samples (0 if not MS texture)

		std::string Name = ResInfo.Name;
		UINT BindPoint = ResInfo.BindPoint;
		D3D_SHADER_INPUT_TYPE Type = ResInfo.Type;

		switch (Type)
		{
		case D3D_SIT_CBUFFER:
		{
			ID3D11ShaderReflectionConstantBuffer* Buffer = CompileInfo->GetConstantBufferByName(Name.c_str());

			D3D11_SHADER_BUFFER_DESC BufferDesc;
			Buffer->GetDesc(&BufferDesc);
			
			GameEngineConstantBuffer* NewBuffer = GameEngineConstantBufferManager::GetInst().
				CreateAndFind(Name, BufferDesc, Buffer);

			if (BufferDesc.Size != NewBuffer->GetBufferSize())
			{
				GameEngineDebug::MsgBoxError("이름은 같고 구조가 다른 상수버퍼가 이미 존재합니다.");
				return;
			}

			ConstantBuffers_.insert(std::make_pair(ResInfo.BindPoint, NewBuffer));
			break;
		}
		case D3D10_SIT_SAMPLER:
		{
			D3D11_SAMPLER_DESC SmpDesc = {};

			// D3D11_FILTER_MIN_MAG_MIP_LINEAR : 뭉개라
			// D3D11_FILTER_MIN_MAG_MIP_POINT : 도트게임처럼 뭉개지않는다.
			SmpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;

			SmpDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
			SmpDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
			SmpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;

			SmpDesc.MipLODBias = 0.0f;
			SmpDesc.MaxAnisotropy = 1;
			SmpDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
			SmpDesc.MinLOD = -FLT_MAX;
			SmpDesc.MaxLOD = FLT_MAX;
			// SmpDesc.BorderColor;
			// SmpDesc.MaxAnisotropy;
			 
			GameEngineSampler* NewRes = GameEngineSamplerManager::GetInst().Create(Name, SmpDesc);
			Samplers_.insert(std::make_pair(ResInfo.BindPoint, NewRes));
			break;
		}
		case D3D_SIT_TEXTURE:
		{
			Textures_.insert(std::make_pair(ResInfo.BindPoint, Name));
			break;
		}
		default:
			GameEngineDebug::MsgBoxError("처리하지 못하는 타입의 쉐이더리소스가 발견되었습니다.");
			break;
		}
	}
}
