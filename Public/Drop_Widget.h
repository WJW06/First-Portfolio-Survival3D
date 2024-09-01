#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Drop_Widget.generated.h"


UCLASS()
class SURVIVAL3D_API UDrop_Widget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, class UDragDropOperation* InOperation) override;
};
