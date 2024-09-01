#include "Tooltip_Widget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"


void UTooltip_Widget::NativeConstruct()
{
	Super::NativeConstruct();
}


void UTooltip_Widget::SetItemData(FItemData& inItemData)
{
	FText priceText = FText::FromString(FString::Printf(TEXT("Price: %d"), itemData.price));
	itemData = inItemData;
	name->SetText(FText::FromName(itemData.itemName));
	price->SetText(priceText);
	amount->SetText(FText::AsNumber(itemData.amount));
	description->SetText(FText::FromString(itemData.description));
	icon->SetBrushFromTexture(itemData.icon);
	icon->SetBrushSize(FVector2D(70, 70));
}