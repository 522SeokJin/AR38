#pragma once
#include <GameEngineBase/GameEngineObjectNameBase.h>
#include "imgui.h"

// Ό³Έν : 
class GameEngineGUIWindow;
class GameEngineGUI
{
	friend class GameEngineCore;
	friend class GameEngineLevel;

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
	template<typename WindowType>
	WindowType* CreateGUIWindow(const std::string& _Name)
	{
		WindowType* NewWindow = new WindowType();

		NewWindow->SetName(_Name);

		Windows_.insert(std::map<std::string, GameEngineGUIWindow*>
			::value_type(_Name, NewWindow));

		return NewWindow;
	}

	GameEngineGUIWindow* FindGUIWindow(const std::string& _Name)
	{
		std::map<std::string, GameEngineGUIWindow*>::iterator FindIter = Windows_.find(_Name);

		if (FindIter == Windows_.end())
		{
			return nullptr;
		}

		return FindIter->second;
	}

protected:
	GameEngineGUI(const GameEngineGUI& _other) = delete; 
	GameEngineGUI(GameEngineGUI&& _other) noexcept = delete;
	GameEngineGUI& operator=(const GameEngineGUI& _other) = delete;
	GameEngineGUI& operator=(const GameEngineGUI&& _other) = delete;

private:
	GameEngineGUI();
	~GameEngineGUI();

	void Initialize();
	void GUIRenderStart();
	void GUIRenderEnd();

	std::map<std::string, GameEngineGUIWindow*> Windows_;

};

class GameEngineGUIWindow : public GameEngineObjectNameBase
{
	friend GameEngineGUI;

public:
	void Begin()
	{
		ImGui::Begin(GetName().c_str(), &GetIsUpdateRef());
	}

	virtual void OnGUI() = 0;

	void End()
	{
		ImGui::End();
	}

protected:
	GameEngineGUIWindow();
	~GameEngineGUIWindow();

	GameEngineGUIWindow(const GameEngineGUIWindow& _Other) = delete;
	GameEngineGUIWindow(GameEngineGUIWindow&& _Other) noexcept = delete;
	GameEngineGUIWindow& operator=(const GameEngineGUIWindow& _Other) = delete;
	GameEngineGUIWindow& operator=(GameEngineGUIWindow&& _Other) noexcept = delete;

private:
};