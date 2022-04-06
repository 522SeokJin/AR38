#pragma once
#include "GameEnginePostProcessRender.h"

struct FadeData
{
	// Fade In, Out
	float Dir_;

	float Speed_;

	// 1, ������ 0�� �ֵ��� ȿ���� ���� ����
	// 0, ������ 0�� �ֵ鵵 ȿ���� �ش�
	int Clip_;

	int Temp;

	FadeData()
		: Dir_(1),
		Speed_(10.0f),
		Clip_(0)
	{

	}
};

// ���� : 
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

