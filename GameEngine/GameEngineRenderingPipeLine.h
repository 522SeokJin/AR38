#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineDevice.h>

// 분류 : 렌더링파이프라인
// 용도 : 렌더링파이프라인을 그림
// 설명 : 렌더링파이프라인을 직접 설정하기위해 만든 클래스

class GameEngineVertexBuffer;
class GameEngineVertexShader;
class GameEngineIndexBuffer;
class GameEngineRasterizer;
class GameEngineRenderingPipeLine : public GameEngineObjectNameBase
{
private:	// member Var
	// VertexBuffer 에서 복사해서 받아온다.
	// IA1
	GameEngineVertexBuffer* VertexBuffer_;
	GameEngineVertexShader* InputLayoutVertexShader_;

	// VS
	GameEngineVertexShader* VertexShader_;
	
	// IA2
	GameEngineIndexBuffer* IndexBuffer_;
	D3D11_PRIMITIVE_TOPOLOGY Topology_;

	GameEngineRasterizer* Rasterizer_;

public:
	
	void SetInputAssembler1VertexBufferSetting(const std::string& _Name);
	void SetInputAssembler1InputLayoutSetting(const std::string& _Name);
	
	void SetVertexShader(const std::string& _Name);

	void SetInputAssembler2IndexBufferSetting(const std::string& _Name);
	void SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY _Topology);

	
	void SetRasterizer(const std::string& _Name);

public:
	// Mesh
	// 부피, 골격과 관련
	// Material -> PipeLine IA 밑에 있는것들
	// 색깔과 관련
	void SetMesh();
	void SetMaterial();

public:
	void Rendering();
	
public:
	GameEngineRenderingPipeLine(); // default constructer 디폴트 생성자
	~GameEngineRenderingPipeLine(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineRenderingPipeLine(const GameEngineRenderingPipeLine& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineRenderingPipeLine(GameEngineRenderingPipeLine&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineRenderingPipeLine& operator=(const GameEngineRenderingPipeLine&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
	void InputAssembler1();
	void VertexShader();
};

