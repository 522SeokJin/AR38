#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν : 
class GameEngineImageRenderer;
class Map : public GameEngineActor
{
public:
	Map();
	virtual ~Map();

	static void SetCurrentMap(Map* _Map)
	{
		CurrentMap = _Map;
	}

	static float4 GetColor(GameEngineTransform* _Ptr, bool _YReverse = true);
	static float4 GetColor(float4 _Position);

	float4 GetMapSize();

	inline GameEngineImageRenderer* GetMapImage()
	{
		return MapImage_;
	}

	inline void SetPixelCollideImage(GameEngineImageRenderer* _Renderer)
	{
		PixelCollideImage_ = _Renderer;
	}

	inline GameEngineImageRenderer* GetPixelCollideImage()
	{
		return PixelCollideImage_;
	}

	static Map* CurrentMap;

protected:
	Map(const Map& _other) = delete; 
	Map(Map&& _other) noexcept = delete;
	Map& operator=(const Map& _other) = delete;
	Map& operator=(const Map&& _other) = delete;

	void Start() override;
	void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) override;

	GameEngineImageRenderer* PixelCollideImage_;

	GameEngineImageRenderer* MapImage_;

private:
};

