#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"
#include "GameEngineShader.h"

// 설명 : 정점의 정보값을 변화시켜서, 물체를 특별한 위치로 옮기거나, 텍스처를 바꾸거나, 색상을 바꾸는 등의 일을 한다.
class GameEngineVertexShader : public GameEngineShader
{
private:	// member Var
	ID3D11VertexShader* Shader_;

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

	bool Load(const std::string& _Path,
		const std::string& _EntryPoint,
		UINT _VersionHigh = 5,
		UINT _VersionLow = 0
	);

	// 수정한 사항에 에러가 없다면 중간에 고쳐도 바로 적용이 된다.
	bool StringCompile();

	bool FileCompile(const std::string& _Path);

	void SetConstantBuffers(const GameEngineConstantBufferSetting* _Setting) override; 
	void SetSamplers(const GameEngineSamplerSetting* _Setting) override;
	void SetTextures(const GameEngineTextureSetting* _Setting) override;

	void ResetConstantBuffers(const GameEngineConstantBufferSetting* _Setting) override;
	void ResetSamplers(const GameEngineSamplerSetting* _Setting) override;
	void ResetTextures(const GameEngineTextureSetting* _Setting) override;

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

