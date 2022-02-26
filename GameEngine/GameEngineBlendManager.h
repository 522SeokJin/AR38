#pragma once
#include "GameEngineDevice.h"

// 설명 : 
class GameEngineBlend;
class GameEngineBlendManager
{
private:
	static GameEngineBlendManager* Inst;

public:
	static GameEngineBlendManager& GetInst()
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
	std::map<std::string, GameEngineBlend*> ResourcesMap;

public:
	// 직접 만들수 있다.
	GameEngineBlend* Create(const std::string& _Name, const D3D11_BLEND_DESC& _Info,
		float4 _Factor = float4::ONE, UINT _Mask = 0xffffffff);
	GameEngineBlend* Find(const std::string& _Name);
	GameEngineBlend* CreateAndFind(const std::string& _Name, const D3D11_BLEND_DESC& _Info,
		float4 _Factor = float4::ONE, UINT _Mask = 0xffffffff);

private: // constrcuter destructer
	GameEngineBlendManager();
	~GameEngineBlendManager();

public: // delete Function
	GameEngineBlendManager(const GameEngineBlendManager& _other) = delete;
	GameEngineBlendManager(GameEngineBlendManager&& _other) noexcept = delete;
	GameEngineBlendManager& operator=(const GameEngineBlendManager& _other) = delete;
	GameEngineBlendManager& operator=(const GameEngineBlendManager&& _other) = delete;

public:

};




