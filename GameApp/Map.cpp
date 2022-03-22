#include "PreCompile.h"
#include "Map.h"
#include <GameEngine/GameEngineImageRenderer.h>

Map* Map::CurrentMap_ = nullptr;

Map::Map()
	: Renderer_(nullptr)
{

}

Map::~Map()
{

}

void Map::Start()
{
}

void Map::LevelChangeStartEvent()
{
}

float4 Map::GetColor(GameEngineTransform* _Ptr)
{
	float4 Pos = _Ptr->GetWorldPosition();

	return CurrentMap_->Renderer_->GetCurTexture()->GetPixel(Pos.ix(), Pos.iy());
}

