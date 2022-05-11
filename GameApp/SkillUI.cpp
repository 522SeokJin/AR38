#include "PreCompile.h"
#include "SkillUI.h"
#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>

SkillUI::SkillUI()
{

}

SkillUI::~SkillUI()
{

}

void SkillUI::Start()
{
	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>();
		Renderer->SetImage("Skill.main.backgrndui.png", true, "PointSmp");
		Renderer->TextSetting("µ¸¿ò", "Àü»ç", 11, float4::WHITE, { 16.0f, 111.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>();
		Renderer->SetImage("info.icon1.png");
		Renderer->SetLocalPosition({ -131.0f, 110.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>();
		Renderer->SetImage("Skill.main.skill1.png");
		Renderer->SetLocalPosition({ -80.0f, 70.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>();
		Renderer->SetImage("Skill.main.skill1.png");
		Renderer->SetLocalPosition({ 63.0f, 70.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>();
		Renderer->SetImage("Skill.main.skill1.png");
		Renderer->SetLocalPosition({ -80.0f, 30.0f });
	}
		
	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>();
		Renderer->SetImage("Skill.main.skill1.png");
		Renderer->SetLocalPosition({ 63.0f, 30.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>();
		Renderer->SetImage("Skill.main.skill1.png");
		Renderer->SetLocalPosition({ -80.0f, -10.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>();
		Renderer->SetImage("Skill.main.skill1.png");
		Renderer->SetLocalPosition({ -80.0f, -50.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>();
		Renderer->SetImage("1001005.icon.png");
		Renderer->SetLocalPosition({ -132.0f, 70.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>();
		Renderer->SetImage("1001005.icon.png");
		Renderer->SetLocalPosition({ 10.0f, 70.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>();
		Renderer->SetImage("1001005.icon.png");
		Renderer->SetLocalPosition({ -132.0f, 30.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>();
		Renderer->SetImage("1001005.icon.png");
		Renderer->SetLocalPosition({ 10.0f, 30.0f });
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>();
		Renderer->SetImage("1001005.icon.png");
		Renderer->SetLocalPosition({ -132.0f, -10.0f });
	}
}

void SkillUI::Update(float _DeltaTime)
{
}

