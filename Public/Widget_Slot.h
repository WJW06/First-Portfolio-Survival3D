#pragma once

#include "ItemData.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Widget_Slot.generated.h"


UCLASS()
class SURVIVAL3D_API UWidget_Slot : public UUserWidget
{
	GENERATED_BODY()
public:
	UWidget_Slot(const FObjectInitializer& ObjectInitializer);
private:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, class UDragDropOperation*& OutOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, class UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, class UDragDropOperation* InOperation) override;
protected:
	virtual void NativeConstruct();
public:
	void SetItemData(struct FItemData& inItemData);
	void SpawnItem();
private:
	UPROPERTY(VisibleAnywhere, Category = "Tooltip")
		TSubclassOf<class UUserWidget> tooltipClass;
	UPROPERTY(VisibleAnywhere, Category = "Tooltip")
		class UWidget_Tooltip* tooltip;
protected:
	UPROPERTY(BlueprintReadOnly, Category = "Slot", meta = (BindWidget))
		class UImage* icon;
	UPROPERTY(BlueprintReadOnly, Category = "Slot")
		class UTexture2D* noneTexture;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Slot")
		struct FItemData itemData;
};
