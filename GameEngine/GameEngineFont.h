#pragma once
#include <GameEngineBase\GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"
#include <ThirdParty\Include\FW1Font\FW1FontWrapper.h>

#pragma comment(lib, "FW1FontWrapper.lib")

// Ό³Έν : 
class GameEngineFontManager;
class GameEngineFont : public GameEngineObjectNameBase
{
	friend GameEngineFontManager;

public:
	GameEngineFont();
	~GameEngineFont();
	
	void DrawFont(const std::string& _Text, float _Size, const float4& _Pos,
		const float4& _Color, unsigned int _Pivot = FW1_CENTER);

protected:
	GameEngineFont(const GameEngineFont& _other) = delete; 
	GameEngineFont(GameEngineFont&& _other) noexcept = delete;
	GameEngineFont& operator=(const GameEngineFont& _other) = delete;
	GameEngineFont& operator=(const GameEngineFont&& _other) = delete;

	void Load(const std::string& _Path);

private:
	static IFW1Factory* FontFactory_;
	IFW1FontWrapper* FontWrapper_;
};

