#pragma once
#include <GameEngineBase\GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineConstantBuffer : public GameEngineObjectNameBase
{
public:
	GameEngineConstantBuffer();
	~GameEngineConstantBuffer();

	inline UINT GetBufferSize()
	{
		return BufferData_.ByteWidth;
	}

	inline ID3D11Buffer*& GetBuffer()
	{
		return Buffer_;
	}

	void Create(const D3D11_SHADER_BUFFER_DESC& _BufferDesc,
		ID3D11ShaderReflectionConstantBuffer* _Buffer);

	void ChangeData(void* _Data, size_t _Size);

protected:
	GameEngineConstantBuffer(const GameEngineConstantBuffer& _other) = delete;
	GameEngineConstantBuffer(GameEngineConstantBuffer&& _other) = delete;
	GameEngineConstantBuffer& operator=(const GameEngineConstantBuffer& _other) = delete; 
	GameEngineConstantBuffer& operator=(const GameEngineConstantBuffer&& _other) = delete;

private:	// member Var
	ID3D11Buffer*					Buffer_;
	D3D11_BUFFER_DESC				BufferData_;
	D3D11_MAPPED_SUBRESOURCE		ResData_;
	D3D11_SHADER_BUFFER_DESC		BufferDesc_;

	std::vector<D3D11_SHADER_VARIABLE_DESC> VarInfos_;
};

