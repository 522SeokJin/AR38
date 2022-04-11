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

	// 1, ������ 0�� �ֵ��� ȿ���� ���� ����
	// 0, ������ 0�� �ֵ鵵 ȿ���� �ش�
	int Clip_;

	float Time_;

	/*FadeData()
	{

	}*/
};

// ���� : 
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

