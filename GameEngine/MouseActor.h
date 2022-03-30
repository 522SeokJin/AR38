#pragma once
#include "GameEngineActor.h"
#include "GameEngineUIRenderer.h"

// Ό³Έν : 
class MouseActor : public GameEngineActor
{
public:
	MouseActor();
	~MouseActor();

	void SetCursor(const std::string& _Name);
	void SetCursor(const std::string& _Name, int _Index);

	GameEngineUIRenderer* GetUIRenderer()
	{
		return UIRenderer_;
	}

	void WindowCursorOn();
	void WindowCursorOff();

protected:
	MouseActor(const MouseActor& _other) = delete; 
	MouseActor(MouseActor&& _other) noexcept = delete;
	MouseActor& operator=(const MouseActor& _other) = delete;
	MouseActor& operator=(const MouseActor&& _other) = delete;

	void Start() override;
	void Update(float _DeltaTime) override;

private:
	GameEngineUIRenderer* UIRenderer_;

};

