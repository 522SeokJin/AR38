#pragma once

// ���� : 
class CameraActor;
class CameraComponent;
class GameEngineActor;
class GameEngineRenderer;
class GameEngineLevel : public GameEngineObjectNameBase
{
	friend class GameEngineCore;
	friend class GameEngineRenderer;

public:
	GameEngineLevel(); // default constructer ����Ʈ ������
	~GameEngineLevel(); // default destructer ����Ʈ �Ҹ���

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
	// int �� ������Ʈ �׷��� ������ ���ϱ������̴�. Ordering
	// ������ ���ٸ�, ���� ������ ���� ���� �ൿ�Ѵ�.
	std::map<int, std::list<GameEngineActor*>> ActorList_;

	CameraActor* MainCameraActor_;
	CameraActor* UICameraActor_;

	////////////////////////////////////////////////////// Renderer

private:
	void Init();
};

