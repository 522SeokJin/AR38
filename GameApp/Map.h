#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν : 
class GameEngineImageRenderer;
class Map : public GameEngineActor
{
public:
	Map();
	virtual ~Map();

	static float4 GetColor(GameEngineTransform* _Ptr, bool _YReverse = true);
	static float4 GetColor(float4 _Position);

	GameEngineImageRenderer* PixelCollideImage_;

protected:
	Map(const Map& _other) = delete; 
	Map(Map&& _other) noexcept = delete;
	Map& operator=(const Map& _other) = delete;
	Map& operator=(const Map&& _other) = delete;

	void Start() override;
	void LevelChangeStartEvent() override;


	inline void SetPixelCollideImage(GameEngineImageRenderer* _Renderer)
	{
		PixelCollideImage_ = _Renderer;
	}

private:
	static Map* CurrentMap;

};

