#include "PreCompile.h"
#include "UserGame.h"
#include <GameEngine\EngineVertex.h>
#include "UserGame_Resources_Shader.h"
#include <GameEngine/GameEngineWindow.h>
#include <GameEngine/GameEngineFontManager.h>

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

	Dir.MoveParent();
	Dir.MoveChild("Image");
	Dir.MoveChild("Image");

	std::vector<GameEngineFile> AllImage = Dir.GetAllDirFile("png");

	for (size_t i = 0; i < AllImage.size(); i++)
	{
		GameEngineTextureManager::GetInst().Load(AllImage[i].GetFullPath());
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
			GameEngineRenderingPipeLineManager::GetInst().Create("PointTextureUI");
		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
		Pipe->SetInputAssembler1InputLayoutSetting("PointTexture_VS");
		Pipe->SetVertexShader("PointTexture_VS");
		Pipe->SetInputAssembler2IndexBufferSetting("Rect");
		Pipe->SetPixelShader("PointTexture_PS");
		Pipe->SetOutputMergerDepthStencil("BaseDepthOff");
	}
}
