#pragma once
#include <string>

// 분류 : 디버거
// 용도 : 메모리관리 메세지 출력 로그
// 설명 : 모든 디버깅 관련 기능은 여기에 모아놓는다.
class GameEngineDebug
{
public:
	static void MsgBoxError(const std::string& _Ptr);
	static void MsgBox(const std::string& _Ptr);
	static void AssertFalse();
	static void OutPutDebugString(const std::string& _Text);

	static void LeakCheckOn();

protected:
	GameEngineDebug();
	~GameEngineDebug();

	GameEngineDebug(const GameEngineDebug& _other) = delete;
	GameEngineDebug(GameEngineDebug&& _other) noexcept = delete;
	GameEngineDebug& operator=(const GameEngineDebug& _other) = delete;
	GameEngineDebug& operator=(const GameEngineDebug&& _other) = delete;

private:

};

