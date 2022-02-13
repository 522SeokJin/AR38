#pragma once
#include <GameEngineBase\GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"

// �з� : 
// �뵵 : 
// ���� : 
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
	GameEngineConstantBuffer(); // default constructer ����Ʈ ������
	~GameEngineConstantBuffer(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineConstantBuffer(const GameEngineConstantBuffer& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineConstantBuffer(GameEngineConstantBuffer&& _other) = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineConstantBuffer& operator=(const GameEngineConstantBuffer& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineConstantBuffer& operator=(const GameEngineConstantBuffer&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	void Create(const D3D11_SHADER_BUFFER_DESC& _BufferDesc, 
		ID3D11ShaderReflectionConstantBuffer* _Buffer);

	void ChangeData(void* _Data, size_t _Size);
};

