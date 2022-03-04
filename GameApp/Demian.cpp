#include "PreCompile.h"
#include "Demian.h"
#include <GameEngine/GameEngineImageRenderer.h>

Demian::Demian()
{

}

Demian::~Demian()
{

}

void Demian::Start()
{
	CreateAnimation();

	DemianRenderer_->ImageLocalFlipYAxis();
}

void Demian::Update(float _DeltaTime)
{
}

