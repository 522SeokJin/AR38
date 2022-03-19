#pragma once
#include "GameEngineDevice.h"

// ���� : 
class GameEngineSampler;
class GameEngineSamplerManager
{
private:
	static GameEngineSamplerManager* Inst;

public:
	static GameEngineSamplerManager& GetInst()
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
	std::map<std::string, GameEngineSampler*> ResourcesMap;

public:
	// ���� ����� �ִ�.
	GameEngineSampler* Create(const std::string& _Name, const D3D11_SAMPLER_DESC& _Info);
	GameEngineSampler* CreateAndFind(const std::string& _Name, const D3D11_SAMPLER_DESC& _Info);
	// ��Ͽ��� ã�´�.
	GameEngineSampler* Find(const std::string& _Name);

private: // constrcuter destructer
	GameEngineSamplerManager();
	~GameEngineSamplerManager();

public: // delete Function
	GameEngineSamplerManager(const GameEngineSamplerManager& _other) = delete;
	GameEngineSamplerManager(GameEngineSamplerManager&& _other) noexcept = delete;
	GameEngineSamplerManager& operator=(const GameEngineSamplerManager& _other) = delete;
	GameEngineSamplerManager& operator=(const GameEngineSamplerManager&& _other) = delete;

public:

};




