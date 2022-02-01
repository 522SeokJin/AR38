#include "PreCompile.h"
#include "GameEngineVertexBuffer.h"

GameEngineVertexBuffer::GameEngineVertexBuffer() // default constructer 디폴트 생성자
	: Buffer_(nullptr)
	, Size_(0)
	, Offset_(0)
	, BufferData_()
	, ResData_()

{
	memset(&BufferData_, 0, sizeof(BufferData_));
	memset(&ResData_, 0, sizeof(ResData_));
}

GameEngineVertexBuffer::~GameEngineVertexBuffer() // default destructer 디폴트 소멸자
{

}

GameEngineVertexBuffer::GameEngineVertexBuffer(GameEngineVertexBuffer&& _other) noexcept  // default RValue Copy constructer 디폴트 RValue 복사생성자
	: Buffer_(_other.Buffer_)
	, Size_(_other.Size_)
	, Offset_(_other.Offset_)
	, BufferData_(_other.BufferData_)
	, ResData_(_other.ResData_)
{

}

void GameEngineVertexBuffer::Create(const void* _Data, size_t _Size, size_t _Count, D3D11_USAGE _Usage)
{
	// 그래픽카드는 그냥 N바이트 자기 메모리에 할당하려고 하니까 정보를 줘야한다.
	// 그 버퍼의
	ResData_.pSysMem = _Data;
	
	BufferData_.ByteWidth = static_cast<UINT>(_Size) * static_cast<UINT>(_Count);
	BufferData_.Usage = _Usage;

	// 건들지 않는다. CPU의 GPU 간섭권한
	BufferData_.CPUAccessFlags = 0;
	//BufferData_.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_READ;
	if (BufferData_.Usage == D3D11_USAGE_DYNAMIC)
	{
		// 매우 느리다.
		BufferData_.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
	}

	// 사용하는 용도를 정함
	BufferData_.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;

	// Default 값, Structured Buffer 는 사용할때만 설정
	BufferData_.StructureByteStride = 0;
	BufferData_.MiscFlags = 0;

	if (S_OK != GameEngineDirectXDevice::GetDevice()->CreateBuffer(&BufferData_, &ResData_, &Buffer_))
	{
		GameEngineDebug::MsgBoxError("VertexBuffer Create Error");
		return;
	}
}

void GameEngineVertexBuffer::Setting()
{
	// IASetVertexBuffer 's' -> 한번에 여러개를 세팅할 수있다.
	// VertexBuffer도 vector로 들고있어야하는데 지금은 1개로 하겠다.
	// _Size도 나중에 vector로 만듬
	GameEngineDirectXDevice::GetContext()->IASetVertexBuffers(0, 1, &Buffer_, &Size_, &Offset_);
}