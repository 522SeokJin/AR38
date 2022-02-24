#pragma once

#include <GameEngineBase/GameEngineSoundManager.h>

#include "GameEngineConstantBufferManager.h"
#include "GameEngineVertexBufferManager.h"
#include "GameEngineVertexShaderManager.h"
#include "GameEngineIndexBufferManager.h"
#include "GameEngineRasterizerManager.h"
#include "GameEnginePixelShaderManager.h"
#include "GameEngineRenderTargetManager.h"
#include "GameEngineTextureManager.h"
#include "GameEngineSamplerManager.h"

#include "GameEngineRenderingPipeLineManager.h"

#include "GameEngineConstantBuffer.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"

#include "GameEngineRenderingPipeLine.h"


class GameEngineManagerHelper
{
public:
	static void ManagerRelease()
	{
		GameEngineSoundManager::Destroy();

		GameEngineRenderingPipeLineManager::Destroy();

		GameEngineConstantBufferManager::Destroy();
		GameEngineVertexBufferManager::Destroy();
		GameEngineVertexShaderManager::Destroy();
		GameEngineIndexBufferManager::Destroy();
		GameEngineRasterizerManager::Destroy();
		GameEngineRenderTargetManager::Destroy();
		GameEnginePixelShaderManager::Destroy();
		GameEngineSamplerManager::Destroy();
		GameEngineTextureManager::Destroy();
	}
};