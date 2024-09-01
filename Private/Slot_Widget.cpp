#include "Slot_Widget.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "Tooltip_Widget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Slot_DragDropOperation.h"
#include "Item.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"


USlot_Widget::USlot_Widget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> noneAsset(TEXT("Texture2D'/Game/Icon/Icons/NoneIcon.NoneIcon'"));

	if (noneAsset.Succeeded())
	{
		noneTexture = noneAsset.Object;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> tooltipAsset(TEXT("WidgetBlueprint'/Game/Blueprint/Widgets/WB_ToolTip.WB_Tooltip_C'"));

	if (tooltipAsset.Succeeded())
	{
		tooltipClass = tooltipAsset.Class;
	}
}


FReply USlot_Widget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
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


void USlot_Widget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);

	if (itemData.amount == 0) return;

	USlot_DragDropOperation* dragDrop = NewObject<USlot_DragDropOperation>();
	SetVisibility(ESlateVisibility::HitTestInvisible);
	dragDrop->itemData = itemData;
	dragDrop->widgetRef = this;
	dragDrop->DefaultDragVisual = this;
	dragDrop->Pivot = EDragPivot::MouseDown;
	OutOperation = dragDrop;
}


void USlot_Widget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);

	SetVisibility(ESlateVisibility::Visible);
}


bool USlot_Widget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);

	USlot_DragDropOperation* dragDrop = Cast<USlot_DragDropOperation>(InOperation);
	if (dragDrop->widgetRef != this)
	{
		FItemData temp = itemData;
		SetItemData(dragDrop->itemData);
		USlot_Widget* newSlot = Cast<USlot_Widget>(dragDrop->widgetRef);
		if (IsValid(newSlot))
		{
			newSlot->SetItemData(temp);
		}
	}
	dragDrop->widgetRef->SetVisibility(ESlateVisibility::Visible);
	SetVisibility(ESlateVisibility::Visible);

	return false;
}


void USlot_Widget::NativeConstruct()
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

	tooltip = Cast<UTooltip_Widget>(CreateWidget(GetWorld(), tooltipClass));
	tooltip->SetItemData(itemData);
}


void USlot_Widget::SetItemData(FItemData& inItemData)
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


void USlot_Widget::SpawnItem()
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