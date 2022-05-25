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
		SkillObjRenderer_->CreateAnimationFolder("Act1_attack1_areaWarning", 0.59f);

		/*SetOffsetAnimation(SkillObjRenderer_, "Act1_attack1_areaWarning", 
			0, { 59.0f, 201.0f } );
		SetOffsetAnimation(SkillObjRenderer_, "Act1_attack1_areaWarning",
			1, { 109.0f, 327.0f });
		SetOffsetAnimation(SkillObjRenderer_, "Act1_attack1_areaWarning",
			2, { 148.0f, 370.0f });
		SetOffsetAnimation(SkillObjRenderer_, "Act1_attack1_areaWarning",
			3, { 177.0f, 389.0f });
		SetOffsetAnimation(SkillObjRenderer_, "Act1_attack1_areaWarning",
			4, { 176.0f, 388.0f });
		SetOffsetAnimation(SkillObjRenderer_, "Act1_attack1_areaWarning",
			5, { 178.0f, 390.0f });
		SetOffsetAnimation(SkillObjRenderer_, "Act1_attack1_areaWarning",
			6, { 178.0f, 389.0f });
		SetOffsetAnimation(SkillObjRenderer_, "Act1_attack1_areaWarning",
			7, { 178.0f, 385.0f });
		SetOffsetAnimation(SkillObjRenderer_, "Act1_attack1_areaWarning",
			8, { 177.0f, 386.0f });
		SetOffsetAnimation(SkillObjRenderer_, "Act1_attack1_areaWarning",
			9, { 177.0f, 386.0f });
		SetOffsetAnimation(SkillObjRenderer_, "Act1_attack1_areaWarning",
			10, { 177.0f, 386.0f });
		SetOffsetAnimation(SkillObjRenderer_, "Act1_attack1_areaWarning",
			11, { 177.0f, 389.0f });*/
	}

	SkillObjRenderer_->SetChangeAnimation("Act1_attack1_areaWarning");
}

void DemianMap::Update(float _DeltaTime)
{
}

float4 DemianMap::CalculationOriginPos(GameEngineImageRenderer* _Renderer, const std::string& _Name, int _Index, const float4& _WzOrigin)
{
	float4 WzCenter = _Renderer->GetAnimationTextureSize(_Name, _Index).halffloat4();

	float4 Center = _Renderer->GetTransform()->GetWorldPosition();

	float4 CenterDiff = Center - WzCenter;
	return (_WzOrigin + CenterDiff).InvertY();
}

