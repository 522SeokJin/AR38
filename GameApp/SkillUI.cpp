#include "PreCompile.h"
#include "SkillUI.h"
#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Mouse.h"

SkillUI::SkillUI()
	: TitleBar_(nullptr)
	, Grabbed_(false)
	, BgRenderer_(nullptr)
	, JobNameRenderer_(nullptr)
	, SkillTab1_(nullptr)
	, SkillTab2_(nullptr)
	, SkillTabCol1_(nullptr)
	, SkillTabCol2_(nullptr)
	, SpUpBtn1_(nullptr)
	, SpUpBtn2_(nullptr)
	, SpUpBtn3_(nullptr)
	, Skill1_(nullptr)
	, Skill2_(nullptr)
	, Skill3_(nullptr)
	, SpUpCol1_(nullptr)
	, SpUpCol2_(nullptr)
	, SpUpCol3_(nullptr)
	, EnabledTab_(0)
	, SP1_(3)
	, SP2_(0)
	, SlashblastSP_(0)
	, WarriorLeapSP_(0)
	, UpperChargeSP_(0)
	, IncisingSP_(0)
	, RagingBlowSP_(0)
	, RageUprisingSP_(0)

{

}

SkillUI::~SkillUI()
{

}

void SkillUI::Start()
{
	{
		BgRenderer_ = CreateTransformComponent<GameEngineUIRenderer>();
		BgRenderer_->SetImage("Skill.main.backgrndui.png", true, "PointSmp");
		BgRenderer_->TextSetting("µ¸¿ò", std::to_string(SP1_), 13.5f, float4::BLACK, { 143.0f, 143.0f });
		BgRenderer_->SetTextFlag(FW1_RIGHT | FW1_VCENTER);
	}

	{
		JobNameRenderer_ = CreateTransformComponent<GameEngineUIRenderer>();
		JobNameRenderer_->SetImage("Skill.main.backgrnd3.png", true, "PointSmp");
		JobNameRenderer_->SetLocalPosition({ 0.0f, 111.0f });
		JobNameRenderer_->TextSetting("µ¸¿ò", "Àü»çÀÇ ±æ", 11, float4::WHITE, { 0.0f, 0.0f });
	}

	{
		SkillTab1_ = CreateTransformComponent<GameEngineUIRenderer>();
		SkillTab1_->SetImage("Skill.main.Tab.enabled.1.png", true, "PointSmp");
		SkillTab1_->SetLocalPosition({ -137.0f + 27.0f * 0.0f, 143.0f });
	}

	{
		SkillTab2_ = CreateTransformComponent<GameEngineUIRenderer>();
		SkillTab2_->SetImage("Skill.main.Tab.disabled.2.png", true, "PointSmp");
		SkillTab2_->SetLocalPosition({ -137.0f + 27.0f * 1.0f, 143.0f });
	}

	{
		SkillTabCol1_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::TAB));
		SkillTabCol1_->SetLocalScaling(SkillTab1_->GetImageSize());
		SkillTabCol1_->SetLocalPosition({ -137.0f + 27.0f * 0.0f, 143.0f });
	}

	{
		SkillTabCol2_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::TAB));
		SkillTabCol2_->SetLocalScaling(SkillTab2_->GetImageSize());
		SkillTabCol2_->SetLocalPosition({ -137.0f + 27.0f * 1.0f, 143.0f });
	}

	{
		SpUpBtn1_ = CreateTransformComponent<GameEngineUIRenderer>();
		SpUpBtn1_->SetImage("Skill.main.BtSpUp.normal.0.png", true, "PointSmp");
		SpUpBtn1_->TextSetting("µ¸¿ò", std::to_string(SlashblastSP_), 13.5f, float4::BLACK, { -90.0f, 0.0f });
		SpUpBtn1_->SetTextFlag(FW1_LEFT | FW1_VCENTER);
		SpUpBtn1_->SetLocalPosition({ -18.0f + 142.0f * 0.0f, 61.5f - 40.0f * 0.0f, -1.0f });
	}

	{
		SpUpBtn2_ = CreateTransformComponent<GameEngineUIRenderer>();
		SpUpBtn2_->SetImage("Skill.main.BtSpUp.normal.0.png", true, "PointSmp");
		SpUpBtn2_->TextSetting("µ¸¿ò", std::to_string(WarriorLeapSP_), 13.5f, float4::BLACK, { -90.0f, 0.0f });
		SpUpBtn2_->SetTextFlag(FW1_LEFT | FW1_VCENTER);
		SpUpBtn2_->SetLocalPosition({ -18.0f + 142.0f * 1.0f, 61.5f - 40.0f * 0.0f, -1.0f });
	}

	{
		SpUpBtn3_ = CreateTransformComponent<GameEngineUIRenderer>();
		SpUpBtn3_->SetImage("Skill.main.BtSpUp.normal.0.png", true, "PointSmp");
		SpUpBtn3_->TextSetting("µ¸¿ò", std::to_string(UpperChargeSP_), 13.5f, float4::BLACK, { -90.0f, 0.0f });
		SpUpBtn3_->SetTextFlag(FW1_LEFT | FW1_VCENTER);
		SpUpBtn3_->SetLocalPosition({ -18.0f + 142.0f * 0.0f, 61.5f - 40.0f * 1.0f, -1.0f });
	}

	{
		SpUpCol1_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::TAB));
		SpUpCol1_->SetLocalScaling(SpUpBtn1_->GetImageSize());
		SpUpCol1_->SetLocalPosition({ -18.0f + 142.0f * 0.0f, 61.5f - 40.0f * 0.0f });
	}

	{
		SpUpCol2_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::TAB));
		SpUpCol2_->SetLocalScaling(SpUpBtn2_->GetImageSize());
		SpUpCol2_->SetLocalPosition({ -18.0f + 142.0f * 1.0f, 61.5f - 40.0f * 0.0f });
	}

	{
		SpUpCol3_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::TAB));
		SpUpCol3_->SetLocalScaling(SpUpBtn3_->GetImageSize());
		SpUpCol3_->SetLocalPosition({ -18.0f + 142.0f * 0.0f, 61.5f - 40.0f * 1.0f });
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
		Skill1_ = CreateTransformComponent<GameEngineUIRenderer>();
		Skill1_->SetImage("1001005.icon.png");
		Skill1_->TextSetting("µ¸¿ò", "½½·¡½Ã ºí·¯½ºÆ®", 13.0f, float4::BLACK, {25.0f, 10.0f});
		Skill1_->SetTextFlag(FW1_LEFT | FW1_VCENTER);
		Skill1_->SetLocalPosition({ -132.0f, 70.0f });
	}

	{
		Skill2_ = CreateTransformComponent<GameEngineUIRenderer>();
		Skill2_->SetImage("1001008.icon.png");
		Skill2_->TextSetting("µ¸¿ò", "¿ö¸®¾î ¸®ÇÁ", 13.0f, float4::BLACK, {25.0f, 10.0f});
		Skill2_->SetTextFlag(FW1_LEFT | FW1_VCENTER);
		Skill2_->SetLocalPosition({ 10.0f, 70.0f });
	}

	{
		Skill3_ = CreateTransformComponent<GameEngineUIRenderer>();
		Skill3_->SetImage("1001011.icon.png");
		Skill3_->TextSetting("µ¸¿ò", "¾îÆÛ Â÷Áö", 13.0f, float4::BLACK, { 25.0f, 10.0f });
		Skill3_->SetTextFlag(FW1_LEFT | FW1_VCENTER);
		Skill3_->SetLocalPosition({ -132.0f, 30.0f });
	}

	{
		TitleBar_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::TAB));
		TitleBar_->SetLocalScaling({ 318.0f, 20.0f });
		TitleBar_->SetLocalPosition({ 0.0f, 168.0f });
	}

}

void SkillUI::Update(float _DeltaTime)
{
	GetLevel()->PushUIDebugRender(TitleBar_->GetTransform(), CollisionType::Rect);

	GetLevel()->PushUIDebugRender(SkillTabCol1_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(SkillTabCol2_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(SpUpCol1_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(SpUpCol2_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(SpUpCol3_->GetTransform(), CollisionType::Rect);

	SpUpBtn1_->SetImage("Skill.main.BtSpUp.normal.0.png", true, "PointSmp");
	SpUpBtn2_->SetImage("Skill.main.BtSpUp.normal.0.png", true, "PointSmp");
	SpUpBtn3_->SetImage("Skill.main.BtSpUp.normal.0.png", true, "PointSmp");

	std::function<void(GameEngineCollision*)> Func =
		std::bind(&SkillUI::TitleBarEvent, this, std::placeholders::_1);

	TitleBar_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);

	Func = std::bind(&SkillUI::SpUpBtnEvent1, this, std::placeholders::_1);

	SpUpCol1_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);

	Func = std::bind(&SkillUI::SpUpBtnEvent2, this, std::placeholders::_1);

	SpUpCol2_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);

	Func = std::bind(&SkillUI::SpUpBtnEvent3, this, std::placeholders::_1);

	SpUpCol3_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);

	ChangeTabEvent();

	switch (EnabledTab_)
	{
	case 0:		// SP1
	
		Skill1_->SetImage("1001005.icon.png");
		Skill1_->TextSetting("µ¸¿ò", "½½·¡½Ã ºí·¯½ºÆ®", 13.0f, float4::BLACK, { 25.0f, 10.0f });
		SpUpBtn1_->TextSetting("µ¸¿ò", std::to_string(SlashblastSP_), 13.5f, float4::BLACK, { -90.0f, 0.0f });

		Skill2_->SetImage("1001008.icon.png");
		Skill2_->TextSetting("µ¸¿ò", "¿ö¸®¾î ¸®ÇÁ", 13.0f, float4::BLACK, { 25.0f, 10.0f });
		SpUpBtn2_->TextSetting("µ¸¿ò", std::to_string(WarriorLeapSP_), 13.5f, float4::BLACK, { -90.0f, 0.0f });
	
		Skill3_->SetImage("1001011.icon.png");
		Skill3_->TextSetting("µ¸¿ò", "¾îÆÛ Â÷Áö", 13.0f, float4::BLACK, { 25.0f, 10.0f });
		SpUpBtn3_->TextSetting("µ¸¿ò", std::to_string(UpperChargeSP_), 13.5f, float4::BLACK, { -90.0f, 0.0f });

		break;
	case 1:		// SP2

		Skill1_->SetImage("1120017.icon.png");
		Skill1_->TextSetting("µ¸¿ò", "·¹ÀÌÂ¡ ºí·Î¿ì", 13.0f, float4::BLACK, { 25.0f, 10.0f });
		SpUpBtn1_->TextSetting("µ¸¿ò", std::to_string(RagingBlowSP_), 13.5f, float4::BLACK, { -90.0f, 0.0f });

		Skill2_->SetImage("1121015.icon.png");
		Skill2_->TextSetting("µ¸¿ò", "ÀÎ»çÀÌÂ¡", 13.0f, float4::BLACK, { 25.0f, 10.0f });
		SpUpBtn2_->TextSetting("µ¸¿ò", std::to_string(IncisingSP_), 13.5f, float4::BLACK, { -90.0f, 0.0f });

		Skill3_->SetImage("1121052.icon.png");
		Skill3_->TextSetting("µ¸¿ò", "·¹ÀÌÁö ¾÷¶óÀÌÂ¡", 13.0f, float4::BLACK, { 25.0f, 10.0f });
		SpUpBtn3_->TextSetting("µ¸¿ò", std::to_string(RageUprisingSP_), 13.5f, float4::BLACK, { -90.0f, 0.0f });

		break;
	default:
		break;
	}


}

void SkillUI::TitleBarEvent(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Down("MLBtn") &&
		false == Grabbed_)
	{
		float4 Value = GetTransform()->GetWorldPosition() - GameEngineInput::GetMouse3DPos();

		GetTransform()->AttachTransform(GlobalValue::CurrentMouse->GetTransform());
		GetTransform()->SetLocalPosition(Value);
		Grabbed_ = true;
	}

	if (true == GameEngineInput::GetInst().Up("MLBtn") &&
		true == Grabbed_)
	{
		GlobalValue::CurrentMouse->GetTransform()->DetachChildTransform(GetTransform());
		Grabbed_ = false;
	}
}

void SkillUI::SpUpBtnEvent1(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Press("MLBtn"))
	{
		SpUpBtn1_->SetImage("Skill.main.BtSpUp.pressed.0.png");
		return;
	}

	if (true == GameEngineInput::GetInst().Up("MLBtn"))
	{
		// Event
		switch (EnabledTab_)
		{
		case 0:		// SP1
			if (0 < SP1_)
			{
				++SlashblastSP_;
				--SP1_;
				BgRenderer_->TextSetting("µ¸¿ò", std::to_string(SP1_), 13.5f, float4::BLACK, { 143.0f, 143.0f });
			}
			break;
		case 1:		// SP2
			if (0 < SP2_)
			{
				++RagingBlowSP_;
				--SP2_;
				BgRenderer_->TextSetting("µ¸¿ò", std::to_string(SP2_), 13.5f, float4::BLACK, { 143.0f, 143.0f });
			}
			break;
		default:
			break;
		}
		return;
	}

	SpUpBtn1_->SetImage("Skill.main.BtSpUp.mouseOver.0.png");
}

void SkillUI::SpUpBtnEvent2(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Press("MLBtn"))
	{
		SpUpBtn2_->SetImage("Skill.main.BtSpUp.pressed.0.png");
		return;
	}

	if (true == GameEngineInput::GetInst().Up("MLBtn"))
	{
		// Event
		switch (EnabledTab_)
		{
		case 0:		// SP1
			if (0 < SP1_)
			{
				++WarriorLeapSP_;
				--SP1_;
				BgRenderer_->TextSetting("µ¸¿ò", std::to_string(SP1_), 13.5f, float4::BLACK, { 143.0f, 143.0f });
			}
			break;
		case 1:		// SP2
			if (0 < SP2_)
			{
				++IncisingSP_;
				--SP2_;
				BgRenderer_->TextSetting("µ¸¿ò", std::to_string(SP2_), 13.5f, float4::BLACK, { 143.0f, 143.0f });
			}
			break;
		default:
			break;
		}
		return;
	}

	SpUpBtn2_->SetImage("Skill.main.BtSpUp.mouseOver.0.png");
}

void SkillUI::SpUpBtnEvent3(GameEngineCollision* _OtherCollision)
{
	if (true == GameEngineInput::GetInst().Press("MLBtn"))
	{
		SpUpBtn3_->SetImage("Skill.main.BtSpUp.pressed.0.png");
		return;
	}

	if (true == GameEngineInput::GetInst().Up("MLBtn"))
	{
		// Event
		switch (EnabledTab_)
		{
		case 0:		// SP1
			if (0 < SP1_)
			{
				++UpperChargeSP_;
				--SP1_;
				BgRenderer_->TextSetting("µ¸¿ò", std::to_string(SP1_), 13.5f, float4::BLACK, { 143.0f, 143.0f });
			}
			break;
		case 1:		// SP2
			if (0 < SP2_)
			{
				++RageUprisingSP_;
				--SP2_;
				BgRenderer_->TextSetting("µ¸¿ò", std::to_string(SP2_), 13.5f, float4::BLACK, { 143.0f, 143.0f });
			}
			break;
		default:
			break;
		}
		return;
	}

	SpUpBtn3_->SetImage("Skill.main.BtSpUp.mouseOver.0.png");
}

void SkillUI::ChangeTabEvent()
{
	SkillTabCol1_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), [&](GameEngineCollision* _OtherCollision)
		{
			if (true == GameEngineInput::GetInst().Down("MLBtn"))
			{
				SkillTab1_->SetImage("Skill.main.Tab.enabled.1.png");
				SkillTab2_->SetImage("Skill.main.Tab.disabled.2.png");

				BgRenderer_->TextSetting("µ¸¿ò", std::to_string(SP1_), 13.5f, float4::BLACK, { 143.0f, 143.0f });
				JobNameRenderer_->TextSetting("µ¸¿ò", "Àü»çÀÇ ±æ", 11, float4::WHITE, { 0.0f, 0.0f });

				EnabledTab_ = 0;
			}
		});

	SkillTabCol2_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), [&](GameEngineCollision* _OtherCollision)
		{
			if (true == GameEngineInput::GetInst().Down("MLBtn"))
			{
				SkillTab1_->SetImage("Skill.main.Tab.disabled.1.png");
				SkillTab2_->SetImage("Skill.main.Tab.enabled.2.png");

				BgRenderer_->TextSetting("µ¸¿ò", std::to_string(SP2_), 13.5f, float4::BLACK, { 143.0f, 143.0f });
				JobNameRenderer_->TextSetting("µ¸¿ò", "È÷¾î·ÎÀÇ ±æ", 11, float4::WHITE, { 0.0f, 0.0f });

				EnabledTab_ = 1;
			}
		});

}

