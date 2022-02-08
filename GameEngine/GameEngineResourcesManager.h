#pragma once

#include <GameEngineBase/GameEngineSoundManager.h>

#include "GameEngineVertexBufferManager.h"
#include "GameEngineVertexShaderManager.h"
#include "GameEngineIndexBufferManager.h"
#include "GameEngineRasterizerManager.h"
#include "GameEnginePixelShaderManager.h"
#include "GameEngineRenderTargetManager.h"
#include "GameEngineTextureManager.h"

#include "GameEngineRenderingPipeLineManager.h"

#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineTexture.h"

#include "GameEngineRenderingPipeLine.h"


class GameEngineManagerHelper
{
public:
	static void ManagerRelease()
	{
		GameEngineSoundManager::Destroy();

		GameEngineRenderingPipeLineManager::Destroy();

		GameEngineVertexBufferManager::Destroy();
		GameEngineVertexShaderManager::Destroy();
		GameEngineIndexBufferManager::Destroy();
		GameEngineRasterizerManager::Destroy();
		GameEngineRenderTargetManager::Destroy();
		GameEnginePixelShaderManager::Destroy();
		GameEngineTextureManager::Destroy();
	}
};