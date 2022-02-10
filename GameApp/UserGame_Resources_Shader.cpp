#include "PreCompile.h"
#include "UserGame_Resources_Shader.h"

void AppShaderLoad()
{
	GameEngineDirectroy Dir;
	Dir.MoveParent("Direct2D");
	Dir.MoveChild("Resources");
	Dir.MoveChild("Shader");

	std::vector<GameEngineFile> AllShader = Dir.GetAllFile("fx");

	for (auto& ShaderFile : AllShader)
	{
		ShaderFile.Open("rt");

		std::string FileName = ShaderFile.GetFileNameWithoutExtension();
		std::string AllCode = ShaderFile.GetString();

		if (std::string::npos != AllCode.find(FileName + "_VS"))
		{
			GameEngineVertexShader* Ptr = GameEngineVertexShaderManager::GetInst().Load(FileName + "_VS", ShaderFile.GetFullPath(), FileName + "_VS");
		}

		if (std::string::npos != AllCode.find(FileName + "_PS"))
		{
			GameEnginePixelShader* Ptr = GameEnginePixelShaderManager::GetInst().Load(FileName + "_PS", ShaderFile.GetFullPath(), FileName + "_PS");
		}
	}



	//{
	//	std::string ShaderCode =
	//		"\
	//		float4 StartVertexShader( float4 pos : POSITION ) : SV_POSITION\n \
	//		{\n \
	//			return pos;\n\
	//		}\n\
	//		";

	//	GameEngineVertexShader* Ptr = GameEngineVertexShaderManager::GetInst().
	//		Create("StartVertexShader", ShaderCode);

	//	//Ptr->AddInputLayout("TEXCOORD", 0, 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
	//	//	0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);
	//	//Ptr->AddInputLayout("POSITION", 0, 16, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
	//	//	0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);
	//	//Ptr->AddInputLayout("COLOR", 0, 32, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
	//	//	0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);
	//}

	//{
	//	std::string ShaderCode =
	//		"\
	//		float4 StartPixelShader( float4 pos : SV_POSITION ) : SV_Target0\n \
	//		{\n \
	//			return float4(1.0f, 0.0f, 0.0f, 1.0f);\n\
	//		}\n\
	//		";

	//	GameEnginePixelShader* Ptr = GameEnginePixelShaderManager::GetInst().
	//		Create("StartPixelShader", ShaderCode);
	//}

}