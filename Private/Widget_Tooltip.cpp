// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget_Tooltip.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UWidget_Tooltip::NativeConstruct()
{
	Super::NativeConstruct();
}

void UWidget_Tooltip::SetItemData(FItemData& inItemData)
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
