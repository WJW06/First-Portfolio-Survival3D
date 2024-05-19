#pragma once

#include "ItemData.h"
#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "DragDropOperation_Slot.generated.h"

UCLASS()
class SURVIVAL3D_API UDragDropOperation_Slot : public UDragDropOperation
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DragDrop")
		UUserWidget* widgetRef;

	FItemData itemData;
};
