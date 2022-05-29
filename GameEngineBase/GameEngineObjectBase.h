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

		return false == IsDeath() &&  // ���� ���׾���
			true == isUpdate_ &&  // ���� �����ְ�
			parent_->isUpdate_; // �θ� �����־��
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
		return isUpdate_; // �θ� �����־����
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

