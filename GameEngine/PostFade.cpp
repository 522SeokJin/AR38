#include "PreCompile.h"
#include "PostFade.h"

PostFade::PostFade(float _Dir, float _Speed, int _Clip)
{
	Data_.Dir_ = _Dir;
	Data_.Speed_ = _Speed;
	Data_.Clip_ = _Clip;
}

PostFade::~PostFade()
{

}

void PostFade::Effect()
{
}

