#include "PreCompile.h"
#include "UserGame.h"
#include "CustomVertex.h"
#include "UserGame_Resources_Shader.h"
#include "GameEngine/GameEngineWindow.h"


void UserGame::ResourceLoad()
{
	GameEngineDirectory Dir;

	Dir.MoveParent();
	Dir.MoveChild("Resources");
	Dir.MoveChild("Sound");

	std::vector<GameEngineFile> AllSound = Dir.GetAllFile("mp3");

	for (size_t i = 0; i < AllSound.size(); i++)
	{
		GameEngineSoundManager::GetInst().Load(AllSound[i].GetFullPath());
	}

	Dir.MoveParent();
	Dir.MoveChild("Image");

	std::vector<GameEngineFile> AllImage = Dir.GetAllDirFile();

	for (size_t i = 0; i < AllImage.size(); i++)
	{
		GameEngineTextureManager::GetInst().Load(AllImage[i].GetFullPath());
	}

	AppShaderLoad();

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

		// D3D11_USAGE : CPU, GPU �б�/����, �׼��������� ����
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

		// CullMode : �޸����Ÿ� ���ؼ� �ʿ��� ���
		// D3D11_CULL_NONE	: ����������� ���� �׷���.
		// D3D11_CULL_FRONT : �ð�������� �׷��� �͵��� �׷���.
		// D3D11_CULL_BACK	: �ð� �ݴ�������� �׷��� �͵��� �׷���.
		Info.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		Info.AntialiasedLineEnable = false;
		Info.MultisampleEnable = false;
		
		// �� �Ű������� TRUE �̸� �ﰢ���� ������ ���� ��󿡼� �ð� �ݴ� �����̸� �������� ���ֵǰ�
		// �ð� �����̸� �ĸ����� ���ֵȴ�. �� �Ű������� FALSE �̸� �� �ݴ�.
		//Info.FrontCounterClockwise = true;
		// ȭ�� �ٱ��� ���� ����� �߶󳽴�.
		//Info.ScissorEnable = true;

		// ���̹��� ����
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
		D3D11_BLEND_DESC BlendInfo = {};

		BlendInfo.AlphaToCoverageEnable = FALSE;
		BlendInfo.IndependentBlendEnable = FALSE;

		BlendInfo.RenderTarget[0].BlendEnable = true;
		BlendInfo.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		// ���� ���� : (SrcColor * SrcFactor) BlendOp (DestColor * DestFactor)
		BlendInfo.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;	// Set Operator
		// ADD -> (SrcColor * SrcFactor) + (DestColor * DestFactor)
		BlendInfo.RenderTarget[0].SrcBlend = D3D11_BLEND::D3D11_BLEND_SRC_ALPHA; // SrcFactor�� �ҽ��� ���İ�����
		BlendInfo.RenderTarget[0].DestBlend = D3D11_BLEND::D3D11_BLEND_INV_SRC_ALPHA;

		// DirectX11 ���� ���Ĵ� ���� ��������
		BlendInfo.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		BlendInfo.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;
		BlendInfo.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_ONE;

		// �������� �����Ҽ�����
		// BlendInfo.RenderTarget[0].DestBlendAlpha = D3D11_BLEND::D3D11_BLEND_BLEND_FACTOR;

		GameEngineBlendManager::GetInst().Create("AlphaBlend", BlendInfo);
	}
	
	// RenderingPipeLine
	{
		GameEngineRenderingPipeLine* Pipe = 
			GameEngineRenderingPipeLineManager::GetInst().Create("Color");

		// �̷� �⺻���� Vertex���� �ִ�.
		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
		Pipe->SetInputAssembler1InputLayoutSetting("Color_VS");

		// �� Vertex�� �̷��� ��ġ��Ű�ڴ�.
		Pipe->SetVertexShader("Color_VS");

		// �� Vertex�� 3���� ��� ������ �׸��ڴ�. ������ �ε��������� �������
		Pipe->SetInputAssembler2IndexBufferSetting("Rect");
		Pipe->SetInputAssembler2TopologySetting(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
 
		// Hull Shader, Tessellator, Domain Shader, Geometry Shader
		// ������ ������ ������, �ʼ��� �ƴϴ�.

		// Vertex�� �� �ɰ��ǵ� �غ� �ϰڴ�.
		// Hull Shader

		// Hull Shader ���� ���Ѵ�� Vertex�� �ɰ���.
		// Tessellator

		// ������ ���ο� Vertex���� �� ����ڴ�.
		// Geometry Shader : ���ӿ��� ���� ���� �ִ�.

		// �׸������ ��, ��� ��ġ�� ������� �ȼ����� �����ϰڴ�.
		Pipe->SetRasterizer("EngineBaseRasterizer");

		Pipe->SetPixelShader("Color_PS");
		Pipe->SetOutputMergerBlend("AlphaBlend");
	}

	{
		GameEngineRenderingPipeLine* Pipe = 
			GameEngineRenderingPipeLineManager::GetInst().Create("Texture");

		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
		Pipe->SetInputAssembler1InputLayoutSetting("Texture_VS");
		Pipe->SetVertexShader("Texture_VS");
		Pipe->SetInputAssembler2IndexBufferSetting("Rect");
		Pipe->SetInputAssembler2TopologySetting(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		Pipe->SetRasterizer("EngineBaseRasterizer");
		Pipe->SetPixelShader("Texture_PS");
		Pipe->SetOutputMergerBlend("AlphaBlend");
	}
}