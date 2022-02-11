#include "PreCompile.h"
#include "GameEngineConstantBuffer.h"

GameEngineConstantBuffer::GameEngineConstantBuffer() // default constructer 디폴트 생성자
	: Buffer_(nullptr)
	, BufferData_()
	, ResData_()
	, BufferDesc_()
{

}

GameEngineConstantBuffer::~GameEngineConstantBuffer() // default destructer 디폴트 소멸자
{
	if (nullptr != Buffer_)
	{
		Buffer_->Release();
		Buffer_ = nullptr;
	}
}

void GameEngineConstantBuffer::Create(const D3D11_SHADER_BUFFER_DESC& _BufferDesc, 
	ID3D11ShaderReflectionConstantBuffer* _Buffer)
{
	BufferDesc_ = _BufferDesc;

	BufferData_.ByteWidth = BufferDesc_.Size;
	// DYNAMIC : CPU에서 계속 정보를 바꿔서 넣어줄 것이다.
	BufferData_.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
	BufferData_.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

	BufferData_.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
	BufferData_.StructureByteStride = 0;
	BufferData_.MiscFlags = 0;

	if (S_OK != GameEngineDevice::GetDevice()->CreateBuffer(&BufferData_, nullptr, &Buffer_))
	{
		GameEngineDebug::MsgBoxError("ConstantBuffer Create Error");
		return;
	}

	for (UINT i = 0; i < BufferDesc_.Variables; i++)
	{
		ID3D11ShaderReflectionVariable* Var = _Buffer->GetVariableByIndex(i);
		D3D11_SHADER_VARIABLE_DESC VarDesc;
		Var->GetDesc(&VarDesc);
		VarInfos_.push_back(VarDesc);
	}
}
