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

void GameEngineConstantBuffer::ChangeData(void* _Data, size_t _Size)
{
	if (BufferData_.ByteWidth != _Size)
	{
		GameEngineDebug::MsgBoxError("상수버퍼 세팅의 크기가 다릅니다. " + GetName());
	}

	memset(&ResData_, 0, sizeof(ResData_));

	// Map : CPU 데이터의 전송을 알림, Buffer_의 데이터를 변경하기위해 렌더링을 정지함
	//		Map을 자주 호출하게되면 느려진다.
	GameEngineDevice::GetContext()->Map(Buffer_, 0, D3D11_MAP_WRITE_DISCARD, 0, &ResData_);

	// CPU에 존재하는 _Data 데이터를 BufferData.ByteWidth 만큼
	// 그래픽카드의 ResData_.pData 로 전송
	memcpy_s(ResData_.pData, BufferData_.ByteWidth, _Data, BufferData_.ByteWidth);

	// UnMap : 전송을 끝내고 다시 이 버퍼가 사용이 가능해진다.
	GameEngineDevice::GetContext()->Unmap(Buffer_, 0);
}
