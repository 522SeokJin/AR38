#include "PreCompile.h"
#include "GameEngineCore.h"
#include "GameEngineWindow.h"
#include "GameEngineResourcesManager.h"
#include "GameEngineCollision.h"
#include "GameEngineBase/GameEngineDirectory.h"
#include "GameEngineBase/GameEngineFile.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineDepthStencil.h"
#include "EngineVertex.h"

void GameEngineCore::EngineResourcesLoad()
{
	{
		GameEngineDirectory Dir;
		Dir.MoveParent();
		Dir.MoveChild("EngineResources");
		Dir.MoveChild("Texture");

		std::vector<GameEngineFile> AllTexture = Dir.GetAllFile();

		for (size_t i = 0; i < AllTexture.size(); i++)
		{
			GameEngineTextureManager::GetInst().Load(AllTexture[i].GetFullPath());
		}
	}

	{
		GameEngineDirectory Dir;
		Dir.MoveParent();
		Dir.MoveChild("EngineResources");
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
	}

	GameEngineSampler* NewRes = GameEngineSamplerManager::GetInst().Find("PointSmp");
	NewRes->Info_.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
	NewRes->ReCreate();
}

void GameEngineCore::EngineResourcesCreate()
{
	{
		std::vector<GameEngineVertex> RectVertex = std::vector<GameEngineVertex>(4 * 6);

		{
			RectVertex[0] = { float4({ -0.5f, 0.5f, 0.5f }) };
			RectVertex[1] = { float4({ 0.5f, 0.5f, 0.5f }) };
			RectVertex[2] = { float4({ 0.5f, -0.5f, 0.5f }) };
			RectVertex[3] = { float4({ -0.5f, -0.5f, 0.5f }) };

			RectVertex[4] = { float4::RotateXDegree(RectVertex[0].Position, 180.0f) };
			RectVertex[5] = { float4::RotateXDegree(RectVertex[1].Position, 180.0f) };
			RectVertex[6] = { float4::RotateXDegree(RectVertex[2].Position, 180.0f) };
			RectVertex[7] = { float4::RotateXDegree(RectVertex[3].Position, 180.0f) };
		}

		{
			RectVertex[8] = { float4::RotateYDegree(RectVertex[0].Position, 90.0f) };
			RectVertex[9] = { float4::RotateYDegree(RectVertex[1].Position, 90.0f) };
			RectVertex[10] = { float4::RotateYDegree(RectVertex[2].Position, 90.0f) };
			RectVertex[11] = { float4::RotateYDegree(RectVertex[3].Position, 90.0f) };

			RectVertex[12] = { float4::RotateYDegree(RectVertex[0].Position, -90.0f) };
			RectVertex[13] = { float4::RotateYDegree(RectVertex[1].Position, -90.0f) };
			RectVertex[14] = { float4::RotateYDegree(RectVertex[2].Position, -90.0f) };
			RectVertex[15] = { float4::RotateYDegree(RectVertex[3].Position, -90.0f) };
		}

		{
			RectVertex[16] = { float4::RotateXDegree(RectVertex[0].Position, 90.0f) };
			RectVertex[17] = { float4::RotateXDegree(RectVertex[1].Position, 90.0f) };
			RectVertex[18] = { float4::RotateXDegree(RectVertex[2].Position, 90.0f) };
			RectVertex[19] = { float4::RotateXDegree(RectVertex[3].Position, 90.0f) };

			RectVertex[20] = { float4::RotateXDegree(RectVertex[0].Position, -90.0f) };
			RectVertex[21] = { float4::RotateXDegree(RectVertex[1].Position, -90.0f) };
			RectVertex[22] = { float4::RotateXDegree(RectVertex[2].Position, -90.0f) };
			RectVertex[23] = { float4::RotateXDegree(RectVertex[3].Position, -90.0f) };
		}


		// UV
		// 0 1	->	0,0		1,0
		// 3 2	->	0,1		1,1

		for (size_t i = 0; i < RectVertex.size(); i += 4)
		{
			RectVertex[i + 0].Texcoord = { 0.0f, 0.0f };
			RectVertex[i + 1].Texcoord = { 1.0f, 0.0f };
			RectVertex[i + 2].Texcoord = { 1.0f, 1.0f };
			RectVertex[i + 3].Texcoord = { 0.0f, 1.0f };
		}

		// D3D11_USAGE : CPU, GPU 읽기/쓰기, 액세스권한을 설정
		GameEngineVertexBufferManager::GetInst().Create("Box", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	{
		std::vector<UINT> RectIndex;

		for (int i = 0; i < 6; i++)
		{
			RectIndex.push_back(i * 4 + 0);
			RectIndex.push_back(i * 4 + 1);
			RectIndex.push_back(i * 4 + 2);

			RectIndex.push_back(i * 4 + 0);
			RectIndex.push_back(i * 4 + 2);
			RectIndex.push_back(i * 4 + 3);
		}

		GameEngineIndexBufferManager::GetInst().Create("Box", RectIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}


	{
		std::vector<GameEngineVertex> RectVertex = std::vector<GameEngineVertex>(4);

		RectVertex[0] = { float4({ -0.5f, 0.5f, 0.0f }),  { 0.0f, 0.0f } };
		RectVertex[1] = { float4({ 0.5f, 0.5f, 0.0f }),  { 1.0f, 0.0f } };
		RectVertex[2] = { float4({ 0.5f, -0.5f, 0.0f }),  { 1.0f, 1.0f } };
		RectVertex[3] = { float4({ -0.5f, -0.5f, 0.0f }),  { 0.0f, 1.0f } };

		GameEngineVertexBufferManager::GetInst().Create("Rect", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	{
		std::vector<UINT> RectIndex;

		RectIndex.push_back(0);
		RectIndex.push_back(1);
		RectIndex.push_back(2);

		RectIndex.push_back(0);
		RectIndex.push_back(2);
		RectIndex.push_back(3);

		GameEngineIndexBufferManager::GetInst().Create("Rect", RectIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}


	{
		std::vector<GameEngineVertex> RectVertex = std::vector<GameEngineVertex>(5);

		{
			// 앞면
			RectVertex[0] = { float4({ -0.5f, 0.5f, 0.0f }),  { 0.0f, 0.0f } };
			RectVertex[1] = { float4({ 0.5f, 0.5f, 0.0f }),  { 1.0f, 0.0f } };
			RectVertex[2] = { float4({ 0.5f, -0.5f, 0.0f }),  { 1.0f, 1.0f } };
			RectVertex[3] = { float4({ -0.5f, -0.5f, 0.0f }),  { 0.0f, 1.0f } };
			RectVertex[4] = { float4({ -0.5f, 0.5f, 0.0f }),  { 0.0f, 0.0f } };
		}

		GameEngineVertexBufferManager::GetInst().Create("DebugRect", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	{
		std::vector<UINT> RectIndex;

		RectIndex.push_back(0);
		RectIndex.push_back(1);
		RectIndex.push_back(2);
		RectIndex.push_back(3);
		RectIndex.push_back(4);

		GameEngineIndexBufferManager::GetInst().Create("DebugRect", RectIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}


	{
		std::vector<GameEngineVertex> RectVertex = std::vector<GameEngineVertex>(4);

		RectVertex[0] = { float4({ -1.0f, 1.0f, 0.0f }), float4({ 0.0f, 0.0f }) };
		RectVertex[1] = { float4({ 1.0f, 1.0f, 0.0f }), float4({ 1.0f, 0.0f }) };
		RectVertex[2] = { float4({ 1.0f, -1.0f, 0.0f }), float4({ 1.0f, 1.0f }) };
		RectVertex[3] = { float4({ -1.0f, -1.0f, 0.0f }),  float4({ 0.0f, 1.0f }) };

		GameEngineVertexBufferManager::GetInst().Create("FullRect", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	{
		std::vector<UINT> RectIndex;

		RectIndex.push_back(0);
		RectIndex.push_back(1);
		RectIndex.push_back(2);

		RectIndex.push_back(0);
		RectIndex.push_back(2);
		RectIndex.push_back(3);

		GameEngineIndexBufferManager::GetInst().Create("FullRect", RectIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	// Rasterizer
	{
		D3D11_RASTERIZER_DESC Info = { D3D11_FILL_MODE::D3D11_FILL_SOLID, };

		Info.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;

		// CullMode : 뒷면제거를 위해서 필요한 모드
		// D3D11_CULL_NONE	: 어느방향으로 돌던 그려라.
		// D3D11_CULL_FRONT : 시계방향으로 그려진 것들을 그려라.
		// D3D11_CULL_BACK	: 시계 반대방향으로 그려진 것들을 그려라.
		Info.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		Info.AntialiasedLineEnable = false;
		Info.MultisampleEnable = false;

		// 이 매개변수가 TRUE 이면 삼각형의 정점이 렌더 대상에서 시계 반대 방향이면 전면으로 간주되고
		// 시계 방향이면 후면으로 간주된다. 이 매개변수가 FALSE 이면 그 반대.
		//Info.FrontCounterClockwise = true;
		// 화면 바깥에 나간 면들을 잘라낸다.
		//Info.ScissorEnable = true;

		// 깊이버퍼 관련
		//Info.SlopeScaledDepthBias = 0;
		//Info.DepthBias = 0;
		//Info.DepthBiasClamp = 0;
		//Info.DepthClipEnable = FALSE;


		GameEngineRasterizer* Ptr = GameEngineRasterizerManager::GetInst().Create("EngineBaseRasterizer", Info);
		Ptr->SetViewPort(GameEngineWindow::GetInst().GetSize().x,
			GameEngineWindow::GetInst().GetSize().y, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	// Blend
	{
		D3D11_BLEND_DESC BlendInfo = {0, };

		BlendInfo.AlphaToCoverageEnable = FALSE;
		BlendInfo.IndependentBlendEnable = FALSE;

		BlendInfo.RenderTarget[0].BlendEnable = true;
		BlendInfo.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		// 블렌드 공식 : (SrcColor * SrcFactor) BlendOp (DestColor * DestFactor)
		BlendInfo.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;	// Set Operator
		// ADD -> (SrcColor * SrcFactor) + (DestColor * DestFactor)
		BlendInfo.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA; // SrcFactor를 소스의 알파값으로
		BlendInfo.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;

		// DirectX11 부터 알파는 따로 설정가능
		BlendInfo.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		BlendInfo.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		BlendInfo.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;

		// 직접값을 지정할수있음
		// BlendInfo.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_BLEND_FACTOR;

		GameEngineBlendManager::GetInst().Create("AlphaBlend", BlendInfo);
	}

	{
		D3D11_DEPTH_STENCIL_DESC DepthInfo = { 0 };

		DepthInfo.DepthEnable = true;
		DepthInfo.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		DepthInfo.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		DepthInfo.StencilEnable = false;

		GameEngineDepthStencilManager::GetInst().Create("BaseDepthOn", DepthInfo);
	}

	{
		D3D11_DEPTH_STENCIL_DESC DepthInfo = { 0 };

		DepthInfo.DepthEnable = false;
		DepthInfo.StencilEnable = false;

		GameEngineDepthStencilManager::GetInst().Create("BaseDepthOff", DepthInfo);
	}

	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("DebugRect");
		Pipe->SetInputAssembler1VertexBufferSetting("DebugRect");
		Pipe->SetInputAssembler1InputLayoutSetting("Color_VS");
		Pipe->SetVertexShader("Color_VS");
		Pipe->SetInputAssembler2IndexBufferSetting("DebugRect");
		Pipe->SetInputAssembler2TopologySetting(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		Pipe->SetPixelShader("Color_PS");
	}

	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("TargetMerge");
		Pipe->SetInputAssembler1VertexBufferSetting("FullRect");
		Pipe->SetInputAssembler1InputLayoutSetting("TargetMerge_VS");
		Pipe->SetVertexShader("TargetMerge_VS");
		Pipe->SetInputAssembler2IndexBufferSetting("FullRect");
		Pipe->SetPixelShader("TargetMerge_PS");
	}


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

	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("TextureUI");
		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
		Pipe->SetInputAssembler1InputLayoutSetting("Texture_VS");
		Pipe->SetVertexShader("Texture_VS");
		Pipe->SetInputAssembler2IndexBufferSetting("Rect");
		Pipe->SetRasterizer("EngineBaseRasterizer");
		Pipe->SetPixelShader("Texture_PS");
		Pipe->SetOutputMergerBlend("AlphaBlend");
		Pipe->SetOutputMergerDepthStencil("BaseDepthOff");
	}
}
