#pragma once

// Ό³Έν : 
class GameEngineFont;
class GameEngineFontManager
{
private:
	static GameEngineFontManager* Inst;

public:
	static GameEngineFontManager& GetInst()
	{
		return *Inst;
	}

	static void Destroy()
	{
		if (nullptr != Inst)
		{
			delete Inst;
			Inst = nullptr;
		}
	}

private: // member Var
	std::map<std::string, GameEngineFont*> ResourcesMap;

public:
	GameEngineFont* Load(const std::string& _Name);

	GameEngineFont* Find(const std::string& _Name);

private: // constrcuter destructer
	GameEngineFontManager();
	~GameEngineFontManager();

public: // delete Function
	GameEngineFontManager(const GameEngineFontManager& _other) = delete;
	GameEngineFontManager(GameEngineFontManager&& _other) noexcept = delete;
	GameEngineFontManager& operator=(const GameEngineFontManager& _other) = delete;
	GameEngineFontManager& operator=(const GameEngineFontManager&& _other) = delete;

public:

};




