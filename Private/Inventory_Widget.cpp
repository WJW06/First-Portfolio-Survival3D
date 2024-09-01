#include "Inventory_Widget.h"
#include "ItemData.h"
#include "Slot_Widget.h"

void UInventory_Widget::NativeConstruct()
{
	Super::NativeConstruct();

	for (int i = 0; i < 30; ++i)
	{
		FName slotName = FName(FString::Printf(TEXT("WB_Slot_%d"), i));
		USlot_Widget* slotWidget = Cast<USlot_Widget>(GetWidgetFromName(slotName));
		if (slotWidget == nullptr)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, TEXT("Not Slot!"));
			return;
		}
		slots.Add(slotWidget);
	}
}


void UInventory_Widget::AddSlotToItem(FItemData& inItemData)
{
	for (USlot_Widget* slotWidget : slots)
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