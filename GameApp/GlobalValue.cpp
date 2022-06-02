#include "PreCompile.h"
#include "GlobalValue.h"



Player* GlobalValue::CurrentPlayer = nullptr;
Mouse* GlobalValue::CurrentMouse = nullptr;
StatusUI* GlobalValue::CurrentStatusUI = nullptr;
ExpBarUI* GlobalValue::CurrentExpBarUI = nullptr;
InventoryUI* GlobalValue::CurrentInventoryUI = nullptr;
SkillUI* GlobalValue::CurrentSkillUI = nullptr;

GlobalValue::GlobalValue()
{

}

GlobalValue::~GlobalValue()
{

}

