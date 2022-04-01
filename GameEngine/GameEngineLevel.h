#pragma once

#include <GameEngine/Enums.h>

// 설명 : 
class CameraActor;
class CameraComponent;
class GameEngineActor;
class GameEngineRenderer;
class GameEngineCollision;
class GameEngineTransform;
class GameEngineLevel : public GameEngineObjectNameBase
{
	friend class GameEngineLevelControlWindow;
	friend class GameEngineCore;
	friend class GameEngineRenderer;
	friend class GameEngineCollision;

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

	void AddTimeEvent(float _Time, std::function<void()> _Event);

protected:
	// delete Function
	GameEngineLevel(const GameEngineLevel& _other) = delete; 
	GameEngineLevel(GameEngineLevel&& _other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _other) = delete;
	GameEngineLevel& operator=(const GameEngineLevel&& _other) = delete;

private:
	void Init();
	void TimeEventUpdate();

	void LevelChangeStartActorEvent();
	void LevelChangeEndActorEvent();

	std::map<int, std::list<GameEngineActor*>> ActorList_;
	CameraActor* MainCameraActor_;
	CameraActor* UICameraActor_;

	std::list<TimeEvent*> AllEvent_;
	std::list<TimeEvent*> AddEvent_;

	//////////////////////////////////////////		Collision
public:
	template<typename UserEnumType>
	void PushCollision(GameEngineCollision* _Collision, UserEnumType _Group)
	{
		PushCollision(_Collision, static_cast<int>(_Group));
	}
	void PushCollision(GameEngineCollision* _Collision, int _Group);

	void PushDebugRender(GameEngineTransform* _Transform, CollisionType _Type);
	void PushUIDebugRender(GameEngineTransform* _Transform, CollisionType _Type);

private:
	inline std::list<GameEngineCollision*>& GetCollisionGroup(int _Group)
	{
		return CollisionList_[_Group];
	}

	void ChangeCollisionGroup(int _Group, GameEngineCollision* _Collision);

	std::map<int, std::list<GameEngineCollision*>> CollisionList_;
};

