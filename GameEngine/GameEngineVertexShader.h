#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include <GameEngine/GameEngineDevice.h>

// 분류 : 렌더링파이프라인 
// 용도 : 버텍스쉐이더
// 설명 : 정점의 정보값을 변화시켜서, 물체를 특별한 위치로 옮기거나, 텍스처를 바꾸거나, 색상을 바꾸는 등의 일을 한다.
class GameEngineVertexShader : public GameEngineObjectNameBase
{
private:	// member Var
	UINT		VersionHigh_;
	UINT		VersionLow_;
	std::string Version_;

	ID3DBlob*	CodeBlob_;
	ID3D11VertexShader* VertexShader_;

	std::string	EntryPoint_;
	std::string Code_;

public:
	GameEngineVertexShader(); // default constructer 디폴트 생성자
	~GameEngineVertexShader(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineVertexShader(const GameEngineVertexShader& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineVertexShader(GameEngineVertexShader&& _other) noexcept = delete; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineVertexShader& operator=(const GameEngineVertexShader& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineVertexShader& operator=(const GameEngineVertexShader&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	bool Create(
		const std::string& _ShaderCode,
		const std::string& _EntryPoint,
		UINT _VersionHigh = 5,
		UINT _VersionLow = 0
	);

	void SetCode(const std::string& _Code);
	void SetEntryPoint(const std::string& _EntryPoint);

	// 수정한 사항에 에러가 없다면 중간에 고쳐도 바로 적용이 된다.
	bool Compile();
	void SetVersion(UINT _VersionHigh, UINT _VersionLow);

private:
	void CreateVersion();

	/// <summary>
	/// ////////////////////////////// InputLayout Settting
	/// </summary>
	// CustomVertex의 순서를 정해준다.
private:
	ID3D11InputLayout*						Layout_;
	unsigned int							LayoutOffset_; // Current Offset Position
	std::vector<std::string>				SemanticName_;
	std::vector<D3D11_INPUT_ELEMENT_DESC>	InputLayoutDesc_;

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

	void LayoutCheck();

	void LayoutClear();

public:
	void InputLayoutSetting();
	void Setting();
};

