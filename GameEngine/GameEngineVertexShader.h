#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include <GameEngine/GameEngineDirectXDevice.h>

// �з� : ���������������� 
// �뵵 : ���ؽ����̴�
// ���� : ������ �������� ��ȭ���Ѽ�, ��ü�� Ư���� ��ġ�� �ű�ų�, �ؽ�ó�� �ٲٰų�, ������ �ٲٴ� ���� ���� �Ѵ�.
class GameEngineVertexShader : public GameEngineObjectNameBase
{
private:	// member Var
	UINT		VersionHigh_;
	UINT		VersionLow_;
	ID3DBlob*	CodeBlob_;
	std::string Version_;

	std::string	EntryPoint_;
	std::string Code_;

public:
	GameEngineVertexShader(); // default constructer ����Ʈ ������
	~GameEngineVertexShader(); // default destructer ����Ʈ �Ҹ���

protected:		// delete constructer
	GameEngineVertexShader(const GameEngineVertexShader& _other) = delete; // default Copy constructer ����Ʈ ���������
	GameEngineVertexShader(GameEngineVertexShader&& _other) noexcept = delete; // default RValue Copy constructer ����Ʈ RValue ���������

private:		//delete operator
	GameEngineVertexShader& operator=(const GameEngineVertexShader& _other) = delete; // default Copy operator ����Ʈ ���� ������
	GameEngineVertexShader& operator=(const GameEngineVertexShader&& _other) = delete; // default RValue Copy operator ����Ʈ RValue ���Կ�����

public:
	bool Create(
		const std::string& _ShaderCode,
		const std::string& _EntryPoint,
		UINT _VersionHigh = 5,
		UINT _VersionLow = 0
	);

	void SetCode(const std::string& _Code);
	void SetEntryPoint(const std::string& _EntryPoint);

	// ������ ���׿� ������ ���ٸ� �߰��� ���ĵ� �ٷ� ������ �ȴ�.
	bool Compile();
	void SetVersion(UINT _VersionHigh, UINT _VersionLow);

private:
	void CreateVersion();

	/// <summary>
	/// ////////////////////////////// InputLayout Settting
	/// </summary>
private:
	ID3D11InputLayout*						Layout_;
	unsigned int							LayoutOffset_;
	std::vector<std::string>				SemanticName_;
	std::vector<D3D11_INPUT_ELEMENT_DESC>	InputLayoutDesc_;

	/*
	CreateInputLayout(...) parameter

	ID3D11InputLayout** ppInputLayout;					-> Layout_
	UINT NumElements;
	SIZE_T BytecodeLength;
	const void* pShaderBytecodeWithInputSignature;
	const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs;	-> InputLayoutDesc_
	*/

public:
	void AddInputLayout(
		const char* _SemanticName,
		unsigned int _SemanticIndex,
		unsigned int _AlignedByteOffset,
		DXGI_FORMAT _Format,
		unsigned int _InputSlot,
		unsigned int _InstanceDataStepRate,
		D3D11_INPUT_CLASSIFICATION _InputClass
	);

	void CreateLayout();
	void LayoutClear();
};

