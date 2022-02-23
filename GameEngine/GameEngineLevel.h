#pragma once


class CameraActor;
class CameraComponent;
class GameEngineActor;
class GameEngineRenderer;
// ���� : 
class GameEngineLevel : public GameEngineObjectNameBase
{
	friend class GameEngineCore;
	friend class GameEngineRenderer;

private:	// member Var
	// int �� ������Ʈ �׷��� ������ ���ϱ������̴�. Ordering
	// ������ ���ٸ�, ���� ������ ���� ���� �ൿ�Ѵ�.
	std::map<int, std::list<GameEngineActor*>> ActorList_;

	CameraActor* MainCameraActor_;
	CameraActor* UICameraActor_;

public:
	CameraActor* GetMainCameraActor();
	CameraComponent* GetMainCamera();

	CameraActor* GetUICameraActor();
	CameraComponent* GetUICamera();

public:
	// constrcuter destructer
	GameEngineLevel(); // default constructer ����Ʈ ������
	~GameEngineLevel(); // default destructer ����Ʈ �Ҹ���

public:
	// delete Function
	GameEngineLevel(const GameEngineLevel& _other) = delete; 
	GameEngineLevel(GameEngineLevel&& _other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _other) = delete;
	GameEngineLevel& operator=(const GameEngineLevel&& _other) = delete;

public:
	template<typename ActorType>
	ActorType* CreateActor(int _UpdateOrder = 0)
	{
		GameEngineActor* NewActor = new ActorType();
		NewActor->SetLevel(this);
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

private:
	void Init();

public:
	virtual void LevelStart() = 0;
	virtual void LevelUpdate(float _DeltaTime) = 0;
	virtual void LevelChangeEndEvent() = 0;
	virtual void LevelChangeStartEvent() = 0;
};

