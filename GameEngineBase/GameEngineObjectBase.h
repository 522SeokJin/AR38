#pragma once

// 분류 : 
// 용도 : 
// 설명 : 
class GameEngineObjectBase
{
private:	// member Var
	// true라고 하는순간 메모리적으로 파괴될겁니다.
	bool isDeath_;
	bool isUpdate_;
	bool isDebug_; // 디버깅 기능 이거 true로 해놓고 f9 걸어 놓으면 
	int Order_;
	bool isOrigin_;
	GameEngineObjectBase* parent_;

public:
	bool isNull()
	{
		return nullptr == this;
	}

	void SetParent(GameEngineObjectBase* _parent)
	{
		parent_ = _parent;
	}

	void SetOrder(int _Order)
	{
		Order_ = _Order;
	}
	
	int GetOrder()
	{
		return Order_;
	}

public:
	bool IsDeath()
	{
		if (nullptr == parent_)
		{
			return isDeath_;
		}

		return true == isDeath_ || parent_->isDeath_;
	}

	bool IsUpdate()
	{
		if (nullptr == parent_)
		{
			return false == IsDeath() && isUpdate_;
		}

		return false == IsDeath() &&  // 나는 안죽었고
			true == isUpdate_ &&  // 내가 켜져있고
			parent_->isUpdate_; // 부모도 켜져있어야
	}

	void CloneOn()
	{
		isOrigin_ = false;
	}

	bool IsClone()
	{
		return isOrigin_ == false;
	}

	void Death()
	{
		isDeath_ = true;
	}

	void OnOffChange()
	{
		isUpdate_ = !isUpdate_;
	}

	void On()
	{
		isUpdate_ = true;
	}

	void Off()
	{
		isUpdate_ = false;
	}

	void DebugOn()
	{
		isDebug_ = true;
	}

	void DebugOff()
	{
		isDebug_ = false;
	}

	bool IsDebugCheck()
	{
		if (true == isDebug_)
		{
			int a = 0;
		}

		return isDebug_;
	}

	bool& GetIsUpdateRef()
	{
		return isUpdate_; // 부모도 켜져있어야함
	}

public:
	GameEngineObjectBase();
	virtual ~GameEngineObjectBase();

protected: // delete fuction
	GameEngineObjectBase(const GameEngineObjectBase& _other) = delete;
	GameEngineObjectBase(GameEngineObjectBase&& _other) noexcept = delete; 
	GameEngineObjectBase& operator=(const GameEngineObjectBase& _other) = delete; 
	GameEngineObjectBase& operator=(const GameEngineObjectBase&& _other) = delete;

public:
};

