#pragma once
#include "GameEnginePostProcessRender.h"

struct FadeData
{
	// Fade In, Out
	float Dir_;

	float Speed_;

	// 1, 투명도가 0인 애들은 효과를 주지 않음
	// 0, 투명도가 0인 애들도 효과를 준다
	int Clip_;

	int Temp;

	FadeData()
		: Dir_(1),
		Speed_(10.0f),
		Clip_(0)
	{

	}
};

// 설명 : 
class PostFade : public GameEnginePostProcessRender
{
public:
	PostFade(float _Dir, float _Speed, int _Clip = 0);
	~PostFade();

protected:
	PostFade(const PostFade& _other) = delete; 
	PostFade(PostFade&& _other) noexcept = delete;
	PostFade& operator=(const PostFade& _other) = delete;
	PostFade& operator=(const PostFade&& _other) = delete;

	void Effect() override;

private:
	FadeData Data_;

};

