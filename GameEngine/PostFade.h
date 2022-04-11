#pragma once
#include "GameEnginePostProcessRender.h"

enum class FadeOption
{
	LIGHT,
	DARK,
};

struct FadeData
{
	float CurTime_;

	float Ratio_;

	// 1, 투명도가 0인 애들은 효과를 주지 않음
	// 0, 투명도가 0인 애들도 효과를 준다
	int Clip_;

	float Time_;

	/*FadeData()
	{

	}*/
};

// 설명 : 
class PostFade : public GameEnginePostProcessRender
{
public:
	PostFade();
	~PostFade();

	void SetData(float _Time, FadeOption _Option);

protected:
	PostFade(const PostFade& _other) = delete; 
	PostFade(PostFade&& _other) noexcept = delete;
	PostFade& operator=(const PostFade& _other) = delete;
	PostFade& operator=(const PostFade&& _other) = delete;

	void Effect(float _DeltaTime) override;
	void Initialize() override;

private:
	FadeData Data_;
	FadeOption Option_;

};

