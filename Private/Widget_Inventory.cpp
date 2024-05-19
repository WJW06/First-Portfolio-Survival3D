#include "Widget_Inventory.h"
#include "ItemData.h"
#include "Widget_Slot.h"

void UWidget_Inventory::NativeConstruct()
{
	Super::NativeConstruct();

	for (int i = 0; i < 30; ++i)
	{
		FName slotName = FName(FString::Printf(TEXT("WB_Slot_%d"), i));
		UWidget_Slot* slotWidget = Cast<UWidget_Slot>(GetWidgetFromName(slotName));
		if (slotWidget == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("Not Slot!"));
			return;
		}
		slots.Add(slotWidget);
	}
}

void UWidget_Inventory::AddSlotToItem(FItemData& inItemData)
{
	for (UWidget_Slot* slotWidget : slots)
	{
		if (slotWidget->itemData == inItemData && inItemData.itemType == EItemType::Item_Equipment)
		{
			continue;
		}
		else if (slotWidget->itemData.amount == 0)
		{
			slotWidget->itemData = inItemData;
			if (inItemData.amount == 0)
			{
				++slotWidget->itemData.amount;
			}
			slotWidget->SetItemData(slotWidget->itemData);
			return;
		}
		else if (slotWidget->itemData == inItemData)
		{
			if (inItemData.amount == 0)
			{
				++slotWidget->itemData.amount;
			}
			slotWidget->itemData.amount += inItemData.amount;
			slotWidget->SetItemData(slotWidget->itemData);
			return;
		}
	}
}