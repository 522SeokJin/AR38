#include "PreCompile.h"
#include "GameEngineShader.h"
#include "GameEngineConstantBufferManager.h"

GameEngineShader::GameEngineShader() // default constructer ����Ʈ ������
	: VersionHigh_(5)
	, VersionLow_(0)
	, CodeBlob_(nullptr)
{

}

GameEngineShader::~GameEngineShader() // default destructer ����Ʈ �Ҹ���
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
		// D3D_SRV_DIMENSION           Dimension;      // Dimension (if texture)	// 3���� �ؽ�ó
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
				GameEngineDebug::MsgBoxError("�̸��� ���� ������ �ٸ� ������۰� �̹� �����մϴ�.");
				return;
			}

			ConstantBuffer_.insert(std::make_pair(ResInfo.BindPoint, NewBuffer));
			break;
		}
		default:
			GameEngineDebug::MsgBoxError("ó������ ���ϴ� Ÿ���� ���̴����ҽ��� �߰ߵǾ����ϴ�.");
			break;
		}
	}
}
