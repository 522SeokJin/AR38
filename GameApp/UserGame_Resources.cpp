#include "PreCompile.h"
#include "UserGame.h"
#include <GameEngine\EngineVertex.h>
#include "UserGame_Resources_Shader.h"
#include <GameEngine/GameEngineWindow.h>
#include <GameEngine/GameEngineFontManager.h>

void TextureLoading(GameEngineDirectory Dir)
{
	std::vector<GameEngineFile> AllFile = Dir.GetAllFile("png");

	for (size_t i = 0; i < AllFile.size(); i++)
	{
		GameEngineTextureManager::GetInst().Load(AllFile[i].GetFullPath());
		// Sleep(1);
	}

	--UserGame::LoadingFolder;
}

void UserGame::ResourceLoad()
{
	GameEngineFontManager::GetInst().Load("±Ã¼­");
	GameEngineFontManager::GetInst().Load("µ¸¿ò");

	GameEngineDirectory Dir;

	Dir.MoveParent();
	Dir.MoveChild("Resources");
	Dir.MoveChild("Sound");

	std::vector<GameEngineFile> AllSound = Dir.GetAllDirFile("mp3");

	for (size_t i = 0; i < AllSound.size(); i++)
	{
		GameEngineSoundManager::GetInst().Load(AllSound[i].GetFullPath());
	}


	{
		Dir.MoveParent();
		Dir.MoveChild("Image");
		Dir.MoveChild("Image");

		std::vector<GameEngineDirectory> AllDir = Dir.GetAllDirectoryRecursive();
		LoadingFolder = static_cast<int>(AllDir.size());

		for (size_t i = 0; i < AllDir.size(); i++)
		{
			GameEngineCore::ThreadQueue.JobPost(std::bind(TextureLoading, AllDir[i]));
		}

		//std::vector<GameEngineFile> AllImage = Dir.GetAllDirFile("png");

		//for (size_t i = 0; i < AllImage.size(); i++)
		//{
		//	GameEngineTextureManager::GetInst().Load(AllImage[i].GetFullPath());
		//}

	}


	Dir.MoveParent();
	Dir.MoveChild("FolderAnimation");

	std::vector<GameEngineFile> AllDir = Dir.GetAllDir();

	for (size_t i = 0; i < AllDir.size(); i++)
	{
		GameEngineFolderTextureManager::GetInst().Load(AllDir[i].GetFullPath());
	}

	AppShaderLoad();

	{
		GameEngineRenderingPipeLine* Pipe =
			GameEngineRenderingPipeLineManager::GetInst().Create("Curved");
		Pipe->SetInputAssembler1VertexBufferSetting("FullRect");
		Pipe->SetInputAssembler1InputLayoutSetting("Curved_VS");
		Pipe->SetVertexShader("Curved_VS");
		Pipe->SetInputAssembler2IndexBufferSetting("FullRect");
		Pipe->SetPixelShader("Curved_PS");
		Pipe->SetOutputMergerDepthStencil("BaseDepthOff");
	}
}
