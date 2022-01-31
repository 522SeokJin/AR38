#pragma once

#include <GameEngineBase/GameEngineSoundManager.h>

#include "GameEngineVertexBufferManager.h"
#include "GameEngineVertexShaderManager.h"
#include "GameEngineIndexBufferManager.h"
#include "GameEngineRasterizerManager.h"
#include "GameEngineRenderTargetManager.h"
#include "GameEngineTextureManager.h"

#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineTexture.h"

class GameEngineManagerHelper
{
public:
	static void ManagerRelease()
	{
		GameEngineSoundManager::Destroy();

		GameEngineVertexBufferManager::Destroy();
		GameEngineVertexShaderManager::Destroy();
		GameEngineIndexBufferManager::Destroy();
		GameEngineRasterizerManager::Destroy();
		GameEngineRenderTargetManager::Destroy();
		GameEngineTextureManager::Destroy();
	}
};