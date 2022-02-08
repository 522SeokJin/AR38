#include "PreCompile.h"
#include "UserGame.h"
#include "CustomVertex.h"


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

	{
		// ���� ��ü�� ������ ũ��� ȸ������ ���� ����
		// ���ý����̽�

		// ���ü��� �ִ� ��ü�� �츮�� ���ϴ� ��� �����ϰ�
		// ��ġ��Ű�� �ν��մϴ�.
		// ���彺���̽�

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

		// D3D11_USAGE : CPU, GPU �б�/����, �׼��������� ����
		GameEngineVertexBufferManager::GetInst().Create("Rect", RectVertex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
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

		GameEngineIndexBufferManager::GetInst().Create("Rect", RectIndex, D3D11_USAGE::D3D11_USAGE_DEFAULT);
	}

	// Vertex Shader
	{
		std::string ShaderCode =
			"\
			float4 StartVertexShader( float4 pos : POSITION ) : SV_POSITION\n \
			{\n \
				return pos;\n\
			}\n\
			";

		GameEngineVertexShader* Ptr = GameEngineVertexShaderManager::GetInst().
			Create("StartVertexShader", ShaderCode);

		//Ptr->AddInputLayout("TEXCOORD", 0, 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		//	0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);
		//Ptr->AddInputLayout("POSITION", 0, 16, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		//	0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);
		//Ptr->AddInputLayout("COLOR", 0, 32, DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT,
		//	0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA);
	}

	{
		std::string ShaderCode =
			"\
			float4 StartPixelShader( float4 pos : SV_POSITION ) : SV_Target0\n \
			{\n \
				return float4(1.0f, 0.0f, 0.0f, 1.0f);\n\
			}\n\
			";

		GameEnginePixelShader* Ptr = GameEnginePixelShaderManager::GetInst().
			Create("StartPixelShader", ShaderCode);
	}

	// Rasterizer
	{
		D3D11_RASTERIZER_DESC Info;

		Info.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;

		// CullMode : �޸����Ÿ� ���ؼ� �ʿ��� ����̴�.
		// D3D11_CULL_NONE	: ����������� ���� �׷���.
		// D3D11_CULL_FRONT : �ð�������� �׷��� �͵��� �׷���.
		// D3D11_CULL_BACK	: �ð� �ݴ�������� �׷��� �͵��� �׷���.
		Info.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;

		// �� �Ű������� TRUE �̸� �ﰢ���� ������ ���� ��󿡼� �ð� �ݴ� �����̸� �������� ���ֵǰ�
		// �ð� �����̸� �ĸ����� ���ֵȴ�. �� �Ű������� FALSE �̸� �� �ݴ�.
		Info.FrontCounterClockwise = TRUE;

		// ȭ�� �ٱ��� ���� ����� �߶󳽴�.
		Info.ScissorEnable = FALSE;

		Info.MultisampleEnable = TRUE;

		// ���̰����� ���� ����
		// ���̹��� ������ ��� �ٷ���Ѵ�.
		Info.SlopeScaledDepthBias = 0;
		Info.DepthBias = 0;
		Info.DepthBiasClamp = 0;
		Info.DepthClipEnable = FALSE;


		GameEngineRasterizer* Ptr = GameEngineRasterizerManager::GetInst().Create("EngineBaseRasterizer", Info);
		Ptr->SetViewPort(1280.0f, 720.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	// RenderingPipeLine
	{
		GameEngineRenderingPipeLine* Pipe = GameEngineRenderingPipeLineManager::GetInst().Create("BoxRendering");

		// �̷� �⺻���� Vertex���� �ִ�.
		Pipe->SetInputAssembler1VertexBufferSetting("Rect");
		Pipe->SetInputAssembler1InputLayoutSetting("StartVertexShader");

		// �� Vertex�� �̷��� ��ġ��Ű�ڴ�.
		Pipe->SetVertexShader("StartVertexShader");

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
		// Rasterizer
		Pipe->SetRasterizer("EngineBaseRasterizer");

		Pipe->SetPixelShader("StartPixelShader");
	}
}
