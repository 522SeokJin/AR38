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


	void Death()
	{
		isDeath_ = true;
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

	void IsDebugCheck()
	{
		if (true == isDebug_)
		{
			int a = 0;
		}
	}

public:
	GameEngineObjectBase(); // default constructer 디폴트 생성자
	virtual ~GameEngineObjectBase(); // default destructer 디폴트 소멸자

protected:		// delete constructer
	GameEngineObjectBase(const GameEngineObjectBase& _other) = delete; // default Copy constructer 디폴트 복사생성자
	GameEngineObjectBase(GameEngineObjectBase&& _other) noexcept; // default RValue Copy constructer 디폴트 RValue 복사생성자

private:		//delete operator
	GameEngineObjectBase& operator=(const GameEngineObjectBase& _other) = delete; // default Copy operator 디폴트 대입 연산자
	GameEngineObjectBase& operator=(const GameEngineObjectBase&& _other) = delete; // default RValue Copy operator 디폴트 RValue 대입연산자

public:
};

