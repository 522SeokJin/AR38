#include "PreCompile.h"
#include "GameEngineString.h"
#include "GameEngineDebug.h"

GameEngineString::GameEngineString() // default constructer ����Ʈ ������
{

}

GameEngineString::~GameEngineString() // default destructer ����Ʈ �Ҹ���
{

}

GameEngineString::GameEngineString(GameEngineString&& _other) noexcept  // default RValue Copy constructer ����Ʈ RValue ���������
{

}

std::string GameEngineString::toupper(const std::string& _Text)
{
	std::string Text = _Text;
	std::transform(Text.begin(), Text.end(), Text.begin(), ::toupper);

	return Text;
}

void GameEngineString::StringToWString(const std::string& _Text, std::wstring& _Out)
{
	int Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0);
	
	if (0 == Size)
	{
		GameEngineDebug::MsgBoxError("��Ʈ�� ��ȯ�� �����߽��ϴ�.");
		return;
	}

	_Out.resize(Size);

	Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), &_Out[0], Size);

	if (0 == Size)
	{
		GameEngineDebug::MsgBoxError("��Ʈ�� ��ȯ�� �����߽��ϴ�.");
		return;
	}
}

std::wstring GameEngineString::StringToWStringReturn(const std::string& _Text)
{
	std::wstring Return;

	int Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), nullptr, 0);

	if (0 == Size)
	{
		GameEngineDebug::MsgBoxError("��Ʈ�� ��ȯ�� �����߽��ϴ�.");
		return L"";
	}

	Return.resize(Size);

	Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), static_cast<int>(_Text.size()), &Return[0], Size);

	if (0 == Size)
	{
		GameEngineDebug::MsgBoxError("��Ʈ�� ��ȯ�� �����߽��ϴ�.");
		return L"";
	}

	return Return;
}
