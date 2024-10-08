#pragma once

#include "ItemData.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Tooltip_Widget.generated.h"

UCLASS()
class SURVIVAL3D_API UTooltip_Widget : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
public:
	void SetItemData(FItemData& inItemData);
private:
	UPROPERTY(VisibleAnywhere, Category = "Tooltip", meta = (BindWidget))
		class UTextBlock* name;
	UPROPERTY(VisibleAnywhere, Category = "Tooltip", meta = (BindWidget))
		class UTextBlock* price;
	UPROPERTY(VisibleAnywhere, Category = "Tooltip", meta = (BindWidget))
		class UTextBlock* amount;
	UPROPERTY(VisibleAnywhere, Category = "Tooltip", meta = (BindWidget))
		class UTextBlock* description;
	UPROPERTY(VisibleAnywhere, Category = "Tooltip", meta = (BindWidget))
		class UImage* icon;
	FItemData itemData;
};
