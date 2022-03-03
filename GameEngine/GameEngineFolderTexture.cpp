#include "PreCompile.h"
#include "GameEngineFolderTexture.h"
#include "GameEngineTexture.h"
#include "GameEngineBase/GameEngineFile.h"
#include "GameEngineBase/GameEngineDirectory.h"

#pragma comment(lib, "DirectXTex.lib")

GameEngineFolderTexture::GameEngineFolderTexture()
{

}

GameEngineFolderTexture::~GameEngineFolderTexture()
{
	for (size_t i = 0; i < AllTextures_.size(); i++)
	{
		if (nullptr != AllTextures_[i])
		{
			delete AllTextures_[i];
			AllTextures_[i] = nullptr;
		}
	}
}

void GameEngineFolderTexture::Load(const std::string& _Path)
{
	GameEngineDirectory TextureDir = _Path;

	std::vector<GameEngineFile> AllFile = TextureDir.GetAllFile();

	for (size_t i = 0; i < AllFile.size(); i++)
	{
		GameEngineTexture* NewRes = new GameEngineTexture();
		NewRes->SetName(AllFile[i].FileName());
		NewRes->Load(AllFile[i].GetFullPath());

		AllTextures_.push_back(NewRes);
	}
}

GameEngineTexture* GameEngineFolderTexture::GetTextureIndex(int _Index)
{
	return AllTextures_[_Index];
}
