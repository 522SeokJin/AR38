#include "PreCompile.h"
#include "UserGame.h"
#include <GameEngine\EngineVertex.h>
#include "UserGame_Resources_Shader.h"
#include <GameEngine/GameEngineWindow.h>

void UserGame::ResourceLoad()
{
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
	Dir.MoveChild("Demian");

	std::vector<GameEngineFile> AllDir = Dir.GetAllDir();

	for (size_t i = 0; i < AllDir.size(); i++)
	{
		GameEngineFolderTextureManager::GetInst().Load(AllDir[i].GetFullPath());
	}

	Dir.MoveParent();
	Dir.MoveChild("Player");

	AllDir = Dir.GetAllDir();

	for (size_t i = 0; i < AllDir.size(); i++)
	{
		GameEngineFolderTextureManager::GetInst().Load(AllDir[i].GetFullPath());
	}

	//AppShaderLoad();

	{
		GameEngineRenderingPipeLine* Pipe = 
			GameEngineRenderingPipeLineManager::GetInst().Create("Color");
		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
		Pipe->SetInputAssembler1InputLayoutSetting("Color_VS");
		Pipe->SetVertexShader("Color_VS");
		Pipe->SetInputAssembler2IndexBufferSetting("Rect");
		Pipe->SetPixelShader("Color_PS");
	}

	{
		GameEngineRenderingPipeLine* Pipe = 
			GameEngineRenderingPipeLineManager::GetInst().Create("Texture");
		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
		Pipe->SetInputAssembler1InputLayoutSetting("Texture_VS");
		Pipe->SetVertexShader("Texture_VS");
		Pipe->SetInputAssembler2IndexBufferSetting("Rect");
		Pipe->SetPixelShader("Texture_PS");
	}
}
