#pragma once

// 분류 : 렌더링파이프라인 
// 용도 : 버텍스쉐이더
// 설명 : 버텍스버퍼를 움직이거나 회전하는걸 할때 사용한다.
class GameEngineVertexShader
{
private:	// member Var
	// virtual float4 VertexShaderFunction(const float4& _Vertex);

public:
	GameEngineVertexShader(); // default constructer 디폴트 생성자
	~GameEngineVertexShader(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineVertexShader(const GameEngineVertexShader& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineVertexShader(GameEngineVertexShader&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineVertexShader& operator=(const GameEngineVertexShader& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineVertexShader& operator=(const GameEngineVertexShader&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};

