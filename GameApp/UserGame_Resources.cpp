#include "PreCompile.h"
#include "UserGame.h"
#include "CustomVertex.h"
#include "UserGame_Resources_Shader.h"
#include "GameEngine/GameEngineWindow.h"


void UserGame::ResourceLoad()
{
	{
		GameEngineDirectroy SoundDir;
		SoundDir.MoveParent("Direct2D");
		SoundDir.MoveChild("Resources");
		SoundDir.MoveChild("Sound");

		std::vector<GameEngineFile> AllFile = SoundDir.GetAllFile("mp3");

		for (size_t i = 0; i < AllFile.size(); i++)
		{
			GameEngineSoundManager::GetInst().LoadSound(AllFile[i].GetFullPath());
		}
	}

	AppShaderLoad();

	{
		// 각자 물체가 각자의 크기와 회전값을 가진 세상
		// 로컬스페이스

		// 로컬세상에 있는 물체를 우리가 원하는 대로 변형하고
		// 위치시키고 인식합니다.
		// 월드스페이스

		std::vector<GameEngineVertex> RectVertex = std::vector<GameEngineVertex>(4 * 6);

		// 0 1
		// 3 2

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

		RectVertex[0] = { float4({ -0.5f, 0.5f, 0.0f }) };
		RectVertex[1] = { float4({ 0.5f, 0.5f, 0.0f }) };
		RectVertex[2] = { float4({ 0.5f, -0.5f, 0.0f }) };
		RectVertex[3] = { float4({ -0.5f, -0.5f, 0.0f }) };

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
		std::vector<GameEngineVertex> RectVertex = std::vector<GameEngineVertex>(4);

		RectVertex[0] = { float4({ -1.0f, 1.0f, 0.0f }) };
		RectVertex[1] = { float4({ 1.0f, 1.0f, 0.0f }) };
		RectVertex[2] = { float4({ 1.0f, -1.0f, 0.0f }) };
		RectVertex[3] = { float4({ -1.0f, -1.0f, 0.0f }) };

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
		Info.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		Info.AntialiasedLineEnable = true;
		Info.MultisampleEnable = true;
		
		// 이 매개변수가 TRUE 이면 삼각형의 정점이 렌더 대상에서 시계 반대 방향이면 전면으로 간주되고
		// 시계 방향이면 후면으로 간주된다. 이 매개변수가 FALSE 이면 그 반대.
		//Info.FrontCounterClockwise = true;
		// 화면 바깥에 나간 면들을 잘라낸다.
		//Info.ScissorEnable = true;

		// 깊이관련은 추후 설명
		// 깊이버퍼 설명을 듣고 다뤄야한다.
		//Info.SlopeScaledDepthBias = 0;
		//Info.DepthBias = 0;
		//Info.DepthBiasClamp = 0;
		//Info.DepthClipEnable = FALSE;


		GameEngineRasterizer* Ptr = GameEngineRasterizerManager::GetInst().Create("EngineBaseRasterizer", Info);
		Ptr->SetViewPort(GameEngineWindow::GetInst().GetSize().x, 
			GameEngineWindow::GetInst().GetSize().y, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	// RenderingPipeLine
	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("Color");

		// 이런 기본적인 Vertex들이 있다.
		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
		Pipe->SetInputAssembler1InputLayoutSetting("Color_VS");

		// 그 Vertex를 이렇게 위치시키겠다.
		Pipe->SetVertexShader("Color_VS");

		// 그 Vertex를 3개로 묶어서 면으로 그리겠다. 순서는 인덱스버퍼의 순서대로
		Pipe->SetInputAssembler2IndexBufferSetting("Rect");
		Pipe->SetInputAssembler2TopologySetting(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
 
		// Hull Shader, Tessellator, Domain Shader, Geometry Shader
		// 있으면 적용이 되지만, 필수는 아니다.

		// Vertex를 더 쪼갤건데 준비를 하겠다.
		// Hull Shader

		// Hull Shader 에서 정한대로 Vertex를 쪼갠다.
		// Tessellator

		// 완전히 새로운 Vertex들을 또 만들겠다.
		// Geometry Shader : 게임에서 쓸모가 많이 있다.

		// 그리기로한 면, 선등에 겹치는 모니터의 픽셀들을 추출하겠다.
		// Rasterizer
		Pipe->SetRasterizer("EngineBaseRasterizer");

		Pipe->SetPixelShader("Color_PS");
	}

	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("TextureRendering");

		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
		Pipe->SetInputAssembler1InputLayoutSetting("Texture_VS");

		Pipe->SetVertexShader("Texture_VS");

		Pipe->SetInputAssembler2IndexBufferSetting("Rect");
		Pipe->SetInputAssembler2TopologySetting(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		Pipe->SetRasterizer("EngineBaseRasterizer");

		Pipe->SetPixelShader("Texture_PS");
	}
}
