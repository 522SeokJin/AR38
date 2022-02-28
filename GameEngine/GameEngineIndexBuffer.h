#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include <GameEngine/GameEngineDevice.h>

// 설명 : 정점들로 어떻게 그릴지 정의를 함, 지금은 3개로 삼각형을 만듬
// 면을 구성하기위한 최소한의 면은 삼각형이기 때문
class GameEngineIndexBuffer : public GameEngineObjectNameBase
{
public:
	GameEngineIndexBuffer();
	~GameEngineIndexBuffer();

	UINT GetIndexCount()
	{
		return IndexCount_;
	}

	void Create(const std::vector<UINT>& _Datas, D3D11_USAGE _Usage);

	void Create(const void* _Data, size_t _Size, size_t _Count, D3D11_USAGE _Usage);

	void Setting();

protected:
	GameEngineIndexBuffer(const GameEngineIndexBuffer& _other) = delete; 
	GameEngineIndexBuffer(GameEngineIndexBuffer&& _other) = delete; 
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer& _other) = delete; 
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer&& _other) = delete;


private:
	ID3D11Buffer*				Buffer_;
	D3D11_BUFFER_DESC			BufferData_;
	D3D11_SUBRESOURCE_DATA		ResData_;
	DXGI_FORMAT					Format_;
	UINT						Offset_;
	UINT						IndexCount_;
};

