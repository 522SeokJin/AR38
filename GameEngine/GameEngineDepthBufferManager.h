#pragma once

// 설명 : 
class GameEngineDepthBuffer;
class GameEngineDepthBufferManager
{
private:
	static GameEngineDepthBufferManager* Inst;

public:
	static GameEngineDepthBufferManager& GetInst()
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
	std::map<std::string, GameEngineDepthBuffer*> ResourcesMap;

public:
	// 직접 만들수 있다.
	GameEngineDepthBuffer* Create(const std::string& _Name, float4 _Size);
	// 파일에서 로드
	GameEngineDepthBuffer* Load(const std::string& _Path);
	// 이름 직접 지정
	GameEngineDepthBuffer* Load(const std::string& _Name, const std::string& _Path);
	// 목록에서 찾는다.
	GameEngineDepthBuffer* Find(const std::string& _Name);

private: // constrcuter destructer
	GameEngineDepthBufferManager();
	~GameEngineDepthBufferManager();

public: // delete Function
	GameEngineDepthBufferManager(const GameEngineDepthBufferManager& _other) = delete;
	GameEngineDepthBufferManager(GameEngineDepthBufferManager&& _other) noexcept = delete;
	GameEngineDepthBufferManager& operator=(const GameEngineDepthBufferManager& _other) = delete;
	GameEngineDepthBufferManager& operator=(const GameEngineDepthBufferManager&& _other) = delete;

public:

};




