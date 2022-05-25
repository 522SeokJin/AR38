#pragma once

// Ό³Έν : 
class GlobalLevelControl
{
public:
	GlobalLevelControl();
	~GlobalLevelControl();

	static void PlayerCameraControl();

protected:
	GlobalLevelControl(const GlobalLevelControl& _other) = delete; 
	GlobalLevelControl(GlobalLevelControl&& _other) noexcept = delete;
	GlobalLevelControl& operator=(const GlobalLevelControl& _other) = delete;
	GlobalLevelControl& operator=(const GlobalLevelControl&& _other) = delete;

private:

};

