#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν : 
class TaxiDlg;
class GameEngineCollision;
class LithHarborTaxi : public GameEngineActor
{
public:
	LithHarborTaxi();
	~LithHarborTaxi();

	void Start() override;
	void Update(float _DeltaTime) override;

	void SetDlg(TaxiDlg* _Dlg)
	{
		Dlg_ = _Dlg;
	}

protected:
	LithHarborTaxi(const LithHarborTaxi& _other) = delete; 
	LithHarborTaxi(LithHarborTaxi&& _other) noexcept = delete;
	LithHarborTaxi& operator=(const LithHarborTaxi& _other) = delete;
	LithHarborTaxi& operator=(const LithHarborTaxi&& _other) = delete;

private:
	TaxiDlg* Dlg_;
	GameEngineCollision* Collision_;
};

