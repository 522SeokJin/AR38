#pragma once
#include "GameEngineDevice.h"

// ���� : 
class GameEngineDepthStencil;
class GameEngineDepthStencilManager
{
private:
	static GameEngineDepthStencilManager* Inst;

public:
	static GameEngineDepthStencilManager& GetInst()
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
	std::map<std::string, GameEngineDepthStencil*> ResourcesMap;

public:
	// ���� ����� �ִ�.
	GameEngineDepthStencil* Create(const std::string& _Name, const D3D11_DEPTH_STENCIL_DESC& _DepthInfo);
	// ���Ͽ��� �ε�
	GameEngineDepthStencil* Load(const std::string& _Path);
	// �̸� ���� ����
	GameEngineDepthStencil* Load(const std::string& _Name, const std::string& _Path);
	// ��Ͽ��� ã�´�.
	GameEngineDepthStencil* Find(const std::string& _Name);

private: // constrcuter destructer
	GameEngineDepthStencilManager();
	~GameEngineDepthStencilManager();

public: // delete Function
	GameEngineDepthStencilManager(const GameEngineDepthStencilManager& _other) = delete;
	GameEngineDepthStencilManager(GameEngineDepthStencilManager&& _other) noexcept = delete;
	GameEngineDepthStencilManager& operator=(const GameEngineDepthStencilManager& _other) = delete;
	GameEngineDepthStencilManager& operator=(const GameEngineDepthStencilManager&& _other) = delete;

public:

};




