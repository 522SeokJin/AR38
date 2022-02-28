#pragma once

// 설명 : 
class CameraActor;
class CameraComponent;
class GameEngineActor;
class GameEngineRenderer;
class GameEngineLevel : public GameEngineObjectNameBase
{
	friend class GameEngineCore;
	friend class GameEngineRenderer;

public:
	GameEngineLevel(); // default constructer 디폴트 생성자
	~GameEngineLevel(); // default destructer 디폴트 소멸자

	virtual void LevelStart() = 0;
	virtual void LevelUpdate(float _DeltaTime) = 0;
	virtual void LevelChangeEndEvent() = 0;
	virtual void LevelChangeStartEvent() = 0;

	CameraActor* GetMainCameraActor();
	CameraComponent* GetMainCamera();

	CameraActor* GetUICameraActor();
	CameraComponent* GetUICamera();

	template<typename ActorType>
	ActorType* CreateActor(float4 _WorldPosition = { 0.0f, 0.0f }, int _UpdateOrder = 0)
	{
		GameEngineActor* NewActor = new ActorType();
		NewActor->SetLevel(this);
		NewActor->GetTransform()->SetWorldPosition(_WorldPosition);
		NewActor->Start();
		NewActor->SetOrder(_UpdateOrder);

		// Insert + Find
		std::list<GameEngineActor*>& List = ActorList_[_UpdateOrder];
		List.push_back(NewActor);

		return dynamic_cast<ActorType*>(NewActor);
	}

	void ActorUpdate(float _DeltaTime);

	void Render();

	void Release(float _DeltaTime);

protected:
	// delete Function
	GameEngineLevel(const GameEngineLevel& _other) = delete; 
	GameEngineLevel(GameEngineLevel&& _other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _other) = delete;
	GameEngineLevel& operator=(const GameEngineLevel&& _other) = delete;

private:
	// int 는 업데이트 그룹의 순서를 정하기위함이다. Ordering
	// 순서가 없다면, 먼저 생성된 것이 먼저 행동한다.
	std::map<int, std::list<GameEngineActor*>> ActorList_;

	CameraActor* MainCameraActor_;
	CameraActor* UICameraActor_;

	////////////////////////////////////////////////////// Renderer

private:
	void Init();
};

