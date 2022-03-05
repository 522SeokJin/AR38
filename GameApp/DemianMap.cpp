#include "PreCompile.h"
#include "DemianMap.h"
#include <GameEngine/GameEngineImageRenderer.h>

DemianMap::DemianMap()
	: SkillObjRenderer_(nullptr)
{

}

DemianMap::~DemianMap()
{

}


void DemianMap::Start()
{
	{
		GameEngineImageRenderer* Renderer = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());
		Renderer->SetImage("20220217153322569_104000000.png");
	}

	SkillObjRenderer_ = CreateTransformComponent<GameEngineImageRenderer>(GetTransform());

	{
		SkillObjRenderer_->CreateAnimationFolder("Act1_attack1_areaWarning", "Act1_attack1_areaWarning", 0.09f);

		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 0, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 1, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 2, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 3, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 4, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 5, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 6, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 7, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 8, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 9, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 10, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 11, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 12, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 13, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 14, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 15, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 16, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 17, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 18, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 19, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 20, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 21, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 22, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 23, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 24, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 25, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 26, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 27, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 28, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 29, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 30, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 31, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 32, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 33, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 34, { 0.0f, 0.0f });
		SkillObjRenderer_->SetOffsetAnimation("Act1_attack1_areaWarning", 35, { 0.0f, 0.0f });
	}

	SkillObjRenderer_->SetChangeAnimation("Act1_attack1_areaWarning");
}

void DemianMap::Update(float _DeltaTime)
{
}
