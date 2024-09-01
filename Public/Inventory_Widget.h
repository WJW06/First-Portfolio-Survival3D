#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Inventory_Widget.generated.h"

UCLASS()
class SURVIVAL3D_API UInventory_Widget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
public:
	void AddSlotToItem(struct FItemData& inItemData);
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Inventory")
		TArray<class USlot_Widget*> slots;
};
