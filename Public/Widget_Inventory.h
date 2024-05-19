#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Inventory.generated.h"


UCLASS()
class SURVIVAL3D_API UWidget_Inventory : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
public:
	void AddSlotToItem(struct FItemData& inItemData);
public:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Inventory")
		TArray<class UWidget_Slot*> slots;
};
