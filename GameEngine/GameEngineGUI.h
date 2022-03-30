#pragma once

// Ό³Έν : 
class GameEngineGUI
{
private:
	static GameEngineGUI* Inst_;

public:
	inline static GameEngineGUI* GetInst()
	{
		return Inst_;
	}

	static void Destroy()
	{
		if (nullptr != Inst_)
		{
			delete Inst_;
			Inst_ = nullptr;
		}
	}

public:
	void Initialize();

	void GUIRenderStart();
	void GUIRenderEnd();

protected:
	GameEngineGUI(const GameEngineGUI& _other) = delete; 
	GameEngineGUI(GameEngineGUI&& _other) noexcept = delete;
	GameEngineGUI& operator=(const GameEngineGUI& _other) = delete;
	GameEngineGUI& operator=(const GameEngineGUI&& _other) = delete;

private:
	GameEngineGUI();
	~GameEngineGUI();

};

