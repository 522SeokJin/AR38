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
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>(GetTransform());
		Renderer->SetImage("mainBar.EXPBar.backgrnd.png");
	}
}

void SkillUI::Update(float _DeltaTime)
{
}

