#include "PreCompile.h"
#include "Map.h"
#include <GameEngine/GameEngineImageRenderer.h>

Map* Map::CurrentMap = nullptr;

Map::Map()
	: PixelCollideImage_(nullptr)
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
	CurrentMap = this;
}

float4 Map::GetColor(GameEngineTransform* _Ptr, bool _YReverse/* = true*/)
{
	float4 Pos = _Ptr->GetWorldPosition();

	std::string TestStr = std::to_string(Pos.x) + " " + std::to_string(Pos.y) + "\n";

	OutputDebugStringA(TestStr.c_str());

	if (true == _YReverse)
	{
		Pos.y *= -1.0f;
	}

	return GetColor(Pos);
}

float4 Map::GetColor(float4 _Position)
{
	return CurrentMap->PixelCollideImage_->GetCurrentTexture()->GetPixel(_Position.ix(), _Position.iy());
}
