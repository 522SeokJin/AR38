#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν : 
class GameEngineImageRenderer;
class Map : public GameEngineActor
{
public:
	Map();
	~Map();

	GameEngineImageRenderer* Renderer_;

protected:
	Map(const Map& _other) = delete; 
	Map(Map&& _other) noexcept = delete;
	Map& operator=(const Map& _other) = delete;
	Map& operator=(const Map&& _other) = delete;

	void Start() override;
	void LevelChangeStartEvent() override;

	static float4 GetColor(GameEngineTransform* _Ptr);

private:
	static Map* CurrentMap_;

};

