#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "GameEngineDevice.h"
#include "ThirdParty/Include/DirectXTex/DirectXTex.h"

// Ό³Έν : 
class GameEngineTexture;
class GameEngineFolderTexture : public GameEngineObjectNameBase
{
public:
	GameEngineFolderTexture();
	~GameEngineFolderTexture();

	void Load(const std::string& _Path);

	GameEngineTexture* GetTextureIndex(int _Index);

	inline int GetTextureCount()
	{
		return static_cast<int>(AllTextures_.size());
	}

	inline std::vector<GameEngineTexture*> GetAllTextures()
	{
		return AllTextures_;
	}

protected:
	GameEngineFolderTexture(const GameEngineFolderTexture& _other) = delete;
	GameEngineFolderTexture(GameEngineFolderTexture&& _other) noexcept = delete;
	GameEngineFolderTexture& operator=(const GameEngineFolderTexture& _other) = delete;
	GameEngineFolderTexture& operator=(const GameEngineFolderTexture&& _other) = delete;

private:
	std::vector<GameEngineTexture*> AllTextures_;
};

