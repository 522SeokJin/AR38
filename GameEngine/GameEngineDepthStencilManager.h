#pragma once
#include "GameEngineDevice.h"

// 설명 : 
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
	// 직접 만들수 있다.
	GameEngineDepthStencil* Create(const std::string& _Name, const D3D11_DEPTH_STENCIL_DESC& _DepthInfo);
	// 파일에서 로드
	GameEngineDepthStencil* Load(const std::string& _Path);
	// 이름 직접 지정
	GameEngineDepthStencil* Load(const std::string& _Name, const std::string& _Path);
	// 목록에서 찾는다.
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




