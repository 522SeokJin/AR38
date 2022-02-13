#pragma once
#include <GameEngineBase\GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineConstantBuffer : public GameEngineObjectNameBase
{
private:	// member Var
	ID3D11Buffer*					Buffer_;
	D3D11_BUFFER_DESC				BufferData_;
	D3D11_MAPPED_SUBRESOURCE		ResData_;
	D3D11_SHADER_BUFFER_DESC		BufferDesc_;

	std::vector<D3D11_SHADER_VARIABLE_DESC> VarInfos_;

public:
	inline UINT GetBufferSize()
	{
		return BufferData_.ByteWidth;
	}

	inline ID3D11Buffer*& GetBuffer()
	{
		return Buffer_;
	}

public:
	GameEngineConstantBuffer(); // default constructer 디폴트 생성자
	~GameEngineConstantBuffer(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineConstantBuffer(const GameEngineConstantBuffer& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineConstantBuffer(GameEngineConstantBuffer&& _other) = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineConstantBuffer& operator=(const GameEngineConstantBuffer& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineConstantBuffer& operator=(const GameEngineConstantBuffer&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void Create(const D3D11_SHADER_BUFFER_DESC& _BufferDesc, 
		ID3D11ShaderReflectionConstantBuffer* _Buffer);

	void ChangeData(void* _Data, size_t _Size);
};

