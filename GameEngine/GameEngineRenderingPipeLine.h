#pragma once
#include <GameEngineBase/GameEngineMath.h>

// 분류 : 렌더링파이프라인
// 용도 : 렌더링파이프라인을 그림
// 설명 : 렌더링파이프라인을 직접 설정하기위해 만든 클래스

class GameEngineVertexBuffer;
class GameEngineVertexShader;
class GameEngineRenderingPipeLine
{
private:	// member Var
	// VertexBuffer 에서 복사해서 받아온다.
	std::vector<float4> CopyVertex;

public:
	void SetInputAssembler1(GameEngineVertexBuffer* _Ptr);
	//void SetVertexShader(GameEngineVertexShader* _Vertex);

	void OutputMerger();
	
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
};

