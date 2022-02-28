#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include <GameEngine/GameEngineDevice.h>

// ���� : ���� ������ ����
class GameEngineVertexBuffer : public GameEngineObjectNameBase
{
public:
	GameEngineVertexBuffer(); // default constructer ����Ʈ ������
	~GameEngineVertexBuffer(); // default destructer ����Ʈ �Ҹ���

	template <typename VertexType>
	void Create(const std::vector<VertexType>& _Datas, D3D11_USAGE _Usage)
	{
		Create(reinterpret_cast<const void*>(&_Datas[0]), sizeof(VertexType), _Datas.size(), _Usage);
	}

	void Create(const void* _Data, size_t _Size, size_t _Count, D3D11_USAGE _Usage);

	void Setting();

protected:
	GameEngineVertexBuffer(const GameEngineVertexBuffer& _other) = delete;
	GameEngineVertexBuffer(GameEngineVertexBuffer&& _other) = delete; 
	GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer& _other) = delete; 
	GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer&& _other) = delete;
	
private:
	ID3D11Buffer*			Buffer_;
	UINT					Size_;
	UINT					Count_;
	UINT					Offset_;

	// ������ ������
	// ������ ũ��
	// ������ ����
	D3D11_BUFFER_DESC		BufferData_;

	// �ʱⰪ���� ������
	D3D11_SUBRESOURCE_DATA	ResData_;
};

