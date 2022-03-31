#pragma once

// Ό³Έν : 
class GameEngineString
{
private:	// member Var

public:
	GameEngineString();
	virtual ~GameEngineString();

protected:		// delete constructer
	GameEngineString(const GameEngineString& _other) = delete;
	GameEngineString(GameEngineString&& _other) noexcept;

private:		//delete operator
	GameEngineString& operator=(const GameEngineString& _other) = delete;
	GameEngineString& operator=(const GameEngineString&& _other) = delete;

public:
	static std::string toupper(const std::string& _Text);

	static void AnsiToUnicode(const std::string& _Text, std::wstring& _Out);
	static void UniCodeToUTF8(const std::wstring& _Text, std::string& _Out);

	static void AnsiToUTF8(const std::string& _Text, std::string& _Out);
	static std::string AnsiToUTF8Return(const std::string& _Text);
	

	static std::wstring AnsiToUnicodeReturn(const std::string& _Text);
};

