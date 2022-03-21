#pragma once

// ���� : 
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
	// ���� ����� �ִ�.
	GameEngineDepthBuffer* Create(const std::string& _Name, float4 _Size);
	// ���Ͽ��� �ε�
	GameEngineDepthBuffer* Load(const std::string& _Path);
	// �̸� ���� ����
	GameEngineDepthBuffer* Load(const std::string& _Name, const std::string& _Path);
	// ��Ͽ��� ã�´�.
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




