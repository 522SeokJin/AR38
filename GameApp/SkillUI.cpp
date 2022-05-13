#include "PreCompile.h"
#include "SkillUI.h"
#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include "Mouse.h"

SkillUI::SkillUI()
	: TitleBar_(nullptr)
	, Grabbed_(false)
	, SkillTab1_(nullptr)
	, SkillTab2_(nullptr)
	, SkillTab3_(nullptr)
	, SkillTab4_(nullptr)
	, SkillTabCol1_(nullptr)
	, SkillTabCol2_(nullptr)
	, SkillTabCol3_(nullptr)
	, SkillTabCol4_(nullptr)
	, EnabledTab_(0)
	, SP1_(0)
	, SP2_(0)
	, SP3_(0)
	, SP4_(0)
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
		Renderer->TextSetting("µ¸¿ò", std::to_string(SP1_), 13.5f, float4::BLACK, { 143.0f, 143.0f });
		Renderer->SetTextFlag(FW1_RIGHT | FW1_VCENTER);
	}

	{
		GameEngineUIRenderer* Renderer = CreateTransformComponent<GameEngineUIRenderer>();
		Renderer->SetImage("Skill.main.backgrnd3.png", true, "PointSmp");
		Renderer->SetLocalPosition({ 0.0f, 111.0f });
		Renderer->TextSetting("µ¸¿ò", "Àü»ç", 11, float4::WHITE, { 0.0f, 0.0f });
	}

	{
		SkillTab1_ = CreateTransformComponent<GameEngineUIRenderer>();
		SkillTab1_->SetImage("Skill.main.Tab.enabled.1.png", true, "PointSmp");
		SkillTab1_->SetLocalPosition({ -137.0f + 27.0f * 0.0f, 143.0f });
	}

	{
		SkillTab2_ = CreateTransformComponent<GameEngineUIRenderer>();
		SkillTab2_->SetImage("Skill.main.Tab.disabled.2.png", true, "PointSmp");
		SkillTab2_->SetLocalPosition({ -137.0f + 26.0f * 1.0f, 143.0f });
	}

	{
		SkillTab3_ = CreateTransformComponent<GameEngineUIRenderer>();
		SkillTab3_->SetImage("Skill.main.Tab.disabled.3.png", true, "PointSmp");
		SkillTab3_->SetLocalPosition({ -137.0f + 26.0f * 2.0f, 143.0f });
	}

	{
		SkillTab4_ = CreateTransformComponent<GameEngineUIRenderer>();
		SkillTab4_->SetImage("Skill.main.Tab.disabled.4.png", true, "PointSmp");
		SkillTab4_->SetLocalPosition({ -137.0f + 26.0f * 3.0f, 143.0f });
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

	{
		TitleBar_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::TAB));
		TitleBar_->SetLocalScaling({ 318.0f, 20.0f });
		TitleBar_->SetLocalPosition({ 0.0f, 168.0f });
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
		SkillTabCol3_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::TAB));
		SkillTabCol3_->SetLocalScaling(SkillTab3_->GetImageSize());
		SkillTabCol3_->SetLocalPosition({ -137.0f + 27.0f * 2.0f, 143.0f });
	}

	{
		SkillTabCol4_ = CreateTransformComponent<GameEngineCollision>(static_cast<int>(
			ColGroup::TAB));
		SkillTabCol4_->SetLocalScaling(SkillTab4_->GetImageSize());
		SkillTabCol4_->SetLocalPosition({ -137.0f + 27.0f * 3.0f, 143.0f });
	}
}

void SkillUI::Update(float _DeltaTime)
{
	GetLevel()->PushUIDebugRender(TitleBar_->GetTransform(), CollisionType::Rect);

	GetLevel()->PushUIDebugRender(SkillTabCol1_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(SkillTabCol2_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(SkillTabCol3_->GetTransform(), CollisionType::Rect);
	GetLevel()->PushUIDebugRender(SkillTabCol4_->GetTransform(), CollisionType::Rect);

	std::function<void(GameEngineCollision*)> Func =
		std::bind(&SkillUI::TitleBarEvent, this, std::placeholders::_1);

	TitleBar_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), Func);

	ChangeTabEvent();
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

void SkillUI::ChangeTabEvent()
{
	SkillTabCol1_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), [&](GameEngineCollision* _OtherCollision)
		{
			if (true == GameEngineInput::GetInst().Down("MLBtn"))
			{
				SkillTab1_->SetImage("Skill.main.Tab.enabled.1.png");
				SkillTab2_->SetImage("Skill.main.Tab.disabled.2.png");
				SkillTab3_->SetImage("Skill.main.Tab.disabled.3.png");
				SkillTab4_->SetImage("Skill.main.Tab.disabled.4.png");

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
				SkillTab3_->SetImage("Skill.main.Tab.disabled.3.png");
				SkillTab4_->SetImage("Skill.main.Tab.disabled.4.png");

				EnabledTab_ = 1;
			}
		});

	SkillTabCol3_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), [&](GameEngineCollision* _OtherCollision)
		{
			if (true == GameEngineInput::GetInst().Down("MLBtn"))
			{
				SkillTab1_->SetImage("Skill.main.Tab.disabled.1.png");
				SkillTab2_->SetImage("Skill.main.Tab.disabled.2.png");
				SkillTab3_->SetImage("Skill.main.Tab.enabled.3.png");
				SkillTab4_->SetImage("Skill.main.Tab.disabled.4.png");

				EnabledTab_ = 2;
			}
		});

	SkillTabCol4_->Collision(CollisionType::Rect, CollisionType::Rect,
		static_cast<int>(ColGroup::MOUSE), [&](GameEngineCollision* _OtherCollision)
		{
			if (true == GameEngineInput::GetInst().Down("MLBtn"))
			{
				SkillTab1_->SetImage("Skill.main.Tab.disabled.1.png");
				SkillTab2_->SetImage("Skill.main.Tab.disabled.2.png");
				SkillTab3_->SetImage("Skill.main.Tab.disabled.3.png");
				SkillTab4_->SetImage("Skill.main.Tab.enabled.4.png");

				EnabledTab_ = 3;
			}
		});
}

