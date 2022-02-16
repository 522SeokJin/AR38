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
	static void toupper(std::string& _Text);
	static void StringToWString(const std::string& _Text, std::wstring& _Out);
};

