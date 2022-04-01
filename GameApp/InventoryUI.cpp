#include "PreCompile.h"
#include "InventoryUI.h"
#include <GameEngine/GameEngineUIRenderer.h>
#include <GameEngine/magic_enum.hpp>
#include "Item.h"

InventoryUI::InventoryUI()
{

}

InventoryUI::~InventoryUI()
{
	for (std::pair<int, std::vector<Item*>> Pair : ItemList_)
	{
		for (size_t i = 0; i < Pair.second.size(); i++)
		{
			if (nullptr != Pair.second[i])
			{
				delete Pair.second[i];
				Pair.second[i] = nullptr;
			}
		}
	}
}

void InventoryUI::Start()
{
	CreateRenderer();
}

void InventoryUI::Update(float _DeltaTime)
{
}


void InventoryUI::PushItem(InventoryCategory _Category, Item* _Item)
{
	if (32 <= ItemList_[static_cast<int>(_Category)].size())
	{
		GameEngineDebug::MsgBoxError("¿Œ∫•≈‰∏Æ æ∆¿Ã≈€ ƒ≠¿Ã ≤À√°Ω¿¥œ¥Ÿ.");
	}

	ItemList_[static_cast<int>(_Category)].push_back(_Item);
}

void InventoryUI::EraseItem(InventoryCategory _Category, int _Index)
{
	if (nullptr != ItemList_[static_cast<int>(_Category)][_Index])
	{
		delete ItemList_[static_cast<int>(_Category)][_Index];
		ItemList_[static_cast<int>(_Category)][_Index] = nullptr;
	}
}