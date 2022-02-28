#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include <GameEngine/GameEngineDevice.h>

// 설명 : 정점 정보를 모음
class GameEngineVertexBuffer : public GameEngineObjectNameBase
{
public:
	GameEngineVertexBuffer(); // default constructer 디폴트 생성자
	~GameEngineVertexBuffer(); // default destructer 디폴트 소멸자

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

	// 버퍼의 데이터
	// 버퍼의 크기
	// 버퍼의 개수
	D3D11_BUFFER_DESC		BufferData_;

	// 초기값등의 데이터
	D3D11_SUBRESOURCE_DATA	ResData_;
};

