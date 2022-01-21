#pragma once

// 분류 : 렌더링파이프라인 
// 용도 : 인덱스버퍼
// 설명 : 정점들로 어떻게 그릴지 정의를 함, 3개로 삼각형을 만듬
//		면을 구성하기위한 최소한의 면은 삼각형이기 때문
class GameEngineIndexBuffer
{
private:	// member Var
	std::vector<int> Indexs;
	// 0 1 3
	// 0 3 2
	// 0 4 1

public:
	GameEngineIndexBuffer(); // default constructer 디폴트 생성자
	~GameEngineIndexBuffer(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineIndexBuffer(const GameEngineIndexBuffer& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineIndexBuffer(GameEngineIndexBuffer&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineIndexBuffer& operator=(const GameEngineIndexBuffer&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};

