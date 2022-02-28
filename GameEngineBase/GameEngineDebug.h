#pragma once
#include <string>

// �з� : �����
// �뵵 : �޸𸮰��� �޼��� ��� �α�
// ���� : ��� ����� ���� ����� ���⿡ ��Ƴ��´�.
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

