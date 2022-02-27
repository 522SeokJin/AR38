#pragma once

// �з� : 
// �뵵 : 
// ���� : 
class GameEngineObjectBase
{
private:	// member Var
	// true��� �ϴ¼��� �޸������� �ı��ɰ̴ϴ�.
	bool isDeath_;
	bool isUpdate_;
	bool isDebug_; // ����� ��� �̰� true�� �س��� f9 �ɾ� ������ 
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

		return false == IsDeath() &&  // ���� ���׾���
			true == isUpdate_ &&  // ���� �����ְ�
			parent_->isUpdate_; // �θ� �����־��
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
	GameEngineObjectBase();
	virtual ~GameEngineObjectBase();

protected: // delete fuction
	GameEngineObjectBase(const GameEngineObjectBase& _other) = delete;
	GameEngineObjectBase(GameEngineObjectBase&& _other) noexcept = delete; 
	GameEngineObjectBase& operator=(const GameEngineObjectBase& _other) = delete; 
	GameEngineObjectBase& operator=(const GameEngineObjectBase&& _other) = delete;

public:
};

