#pragma once

#include <GameEngine/Enums.h>

// 설명 : 
class CameraActor;
class CameraComponent;
class GameEngineActor;
class GameEngineRenderer;
class GameEngineCollision;
class GameEngineTransform;
class GameEnginePostProcessRender;
class GameEngineLevel : public GameEngineObjectNameBase
{
	friend class GameEngineLevelControlWindow;
	friend class GameEngineCore;
	friend class GameEngineRenderer;
	friend class GameEngineCollision;

private:
	// for문 중간에 삭제하는걸 방지하기 위함
	class NextLevelActor
	{
	public:
		GameEngineActor* Actor;
		GameEngineLevel* Level;
	};

public:
	GameEngineLevel(); // default constructer 디폴트 생성자
	~GameEngineLevel(); // default destructer 디폴트 소멸자

	virtual void LevelStart() = 0;
	virtual void LevelUpdate(float _DeltaTime) = 0;
	virtual void LevelChangeEndEvent(GameEngineLevel* _NextLevel) = 0;
	virtual void LevelChangeStartEvent(GameEngineLevel* _PrevLevel) = 0;

	void SetLevelActorMove(GameEngineLevel* _NextLevel, GameEngineActor* _Actor);
	void SetLevelActorMoveProcess();

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

	template<typename ActorType>
	ActorType* CreateActor(std::string _Name, bool _IsFind = false, int _UpdateOrder = 0)
	{
		GameEngineActor* NewActor = new ActorType();
		NewActor->IsFindObject_ = _IsFind;
		NewActor->SetName(_Name);
		NewActor->SetLevel(this);
		NewActor->Start();
		NewActor->SetOrder(_UpdateOrder);

		if (true == _IsFind)
		{
			FindMap_.insert(std::make_pair(_Name, NewActor));
		}

		// Insert + Find
		std::list<GameEngineActor*>& List = ActorList_[_UpdateOrder];
		List.push_back(NewActor);
		return dynamic_cast<ActorType*>(NewActor);
	}

	template<typename ActorType>
	ActorType* FindActor(std::string _Name)
	{
		if (FindMap_.end() == FindMap_.find(_Name))
		{
			return nullptr;
		}

		return dynamic_cast<ActorType>(FindMap_[_Name]);
	}

	void ActorUpdate(float _DeltaTime);

	void Render(float _DeltaTime);

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

	void LevelChangeStartActorEvent(GameEngineLevel* _PrevLevel);
	void LevelChangeEndActorEvent(GameEngineLevel* _NextLevel);

	std::vector<NextLevelActor> NextLevelActorsData_;
	std::map<std::string, GameEngineActor*> FindMap_;
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

	void PushDebugRender(GameEngineCollision* _Collision, CollisionType _Type);
	void PushUIDebugRender(GameEngineCollision* _Collision, CollisionType _Type);

	inline std::list<GameEngineCollision*>& GetCollisionGroup(int _Group)
	{
		return CollisionList_[_Group];
	}

private:

	void ChangeCollisionGroup(int _Group, GameEngineCollision* _Collision);

	std::map<int, std::list<GameEngineCollision*>> CollisionList_;


////////////////////////////////////////////////// GameEnginePostProcessRender

public:
	template<typename PostProcess, typename ... Parameter>
	PostProcess* AddPostProcessCameraMergePrev(Parameter ... _Arg)
	{
		return AddPostProcess<PostProcess>("CameraMergePrev", _Arg...);
	}

	template<typename PostProcess, typename ... Parameter>
	PostProcess* AddPostProcessCameraMergeNext(Parameter ... _Arg)
	{
		return AddPostProcess<PostProcess>("CameraMergeNext", _Arg...);
	}

	template<typename PostProcess, typename ... Parameter>
	PostProcess* AddPostProcess(const std::string& _Key, Parameter ... _Arg)
	{
		PostProcess* NewPost = new PostProcess(_Arg...);
		PostRender_[_Key].push_back(NewPost);
		GameEnginePostProcessRender* ParentType = dynamic_cast<GameEnginePostProcessRender*>(NewPost);
		ParentType->Initialize();
		return NewPost;
	}

	void AllClear();

private:
	std::map<std::string, std::vector<GameEnginePostProcessRender*>> PostRender_;
};

