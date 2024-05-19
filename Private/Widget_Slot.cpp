#include "Widget_Slot.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "Widget_Tooltip.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "DragDropOperation_Slot.h"
#include "Item.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UWidget_Slot::UWidget_Slot(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> noneAsset(TEXT(""));

	if (noneAsset.Succeeded())
	{
		noneTexture = noneAsset.Object;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> tooltipAsset(TEXT(""));

	if (tooltipAsset.Succeeded())
	{
		tooltipClass = tooltipAsset.Class;
	}
}

FReply UWidget_Slot::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FEventReply reply;
	reply.NativeReply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);

	if (InMouseEvent.IsMouseButtonDown(FKey("LeftMouseButton")))
	{
		reply = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
	}

	if (InMouseEvent.IsMouseButtonDown(FKey("RightMouseButton")))
	{
		if (itemData.itemType == EItemType::Item_Useable)
		{
			--itemData.amount;
			tooltip->SetItemData(itemData);
			if (itemData.amount <= 0)
			{
				FItemData temp;
				itemData = temp;
				SetItemData(itemData);
			}
		}
	}

	return reply.NativeReply;
}

void UWidget_Slot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (itemData.amount == 0) return;

	UDragDropOperation_Slot* dragDrop = NewObject<UDragDropOperation_Slot>();
	SetVisibility(ESlateVisibility::HitTestInvisible);
	dragDrop->itemData = itemData;
	dragDrop->widgetRef = this;
	dragDrop->DefaultDragVisual = this;
	dragDrop->Pivot = EDragPivot::MouseDown;
	OutOperation = dragDrop;
}

void UWidget_Slot::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	SetVisibility(ESlateVisibility::Visible);
}

bool UWidget_Slot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	UDragDropOperation_Slot* dragDrop = Cast<UDragDropOperation_Slot>(InOperation);
	if (dragDrop->widgetRef != this)
	{
		FItemData temp = itemData;
		SetItemData(dragDrop->itemData);
		UWidget_Slot* newSlot = Cast<UWidget_Slot>(dragDrop->widgetRef);
		if (IsValid(newSlot))
		{
			newSlot->SetItemData(temp);
		}
	}
	dragDrop->widgetRef->SetVisibility(ESlateVisibility::Visible);
	SetVisibility(ESlateVisibility::Visible);

	return false;
}

void UWidget_Slot::NativeConstruct()
{
	Super::NativeConstruct();

	if (itemData.amount == 0)
	{
		icon->SetBrushFromTexture(noneTexture);
	}
	else
	{
		icon->SetBrushFromTexture(itemData.icon);
		icon->SetBrushSize(FVector2D(70, 70));
	}

	tooltip = Cast<UWidget_Tooltip>(CreateWidget(GetWorld(), tooltipClass));
	tooltip->SetItemData(itemData);
}

void UWidget_Slot::SetItemData(FItemData& inItemData)
{
	itemData = inItemData;
	if (itemData.amount == 0)
	{
		icon->SetBrushFromTexture(noneTexture);
		icon->SetToolTip(nullptr);
	}
	else
	{
		icon->SetBrushFromTexture(itemData.icon);
		icon->SetBrushSize(FVector2D(70, 70));
		tooltip->SetItemData(itemData);
		icon->SetToolTip(tooltip);
	}
}

void UWidget_Slot::SpawnItem()
{
	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	FTransform transform = player->GetActorTransform();
	transform.SetLocation(player->GetActorLocation() + (player->GetActorForwardVector() * 200));
	AItem* item = GetWorld()->SpawnActorDeferred<AItem>(AItem::StaticClass(), transform);
	item->SetItemRowName(itemData.itemName);
	item->FinishSpawning(item->GetTransform());
	item->SetItemData(itemData);

	FItemData temp;
	itemData = temp;
	SetItemData(itemData);
}