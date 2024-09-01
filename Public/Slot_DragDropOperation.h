#pragma once

#include "ItemData.h"
#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "Slot_DragDropOperation.generated.h"


UCLASS()
class SURVIVAL3D_API USlot_DragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DragDrop")
		UUserWidget* widgetRef;

	FItemData itemData;
};