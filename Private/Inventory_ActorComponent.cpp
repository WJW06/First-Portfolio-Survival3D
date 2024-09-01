#include "Inventory_ActorComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Inventory_Widget.h"

UInventory_ActorComponent::UInventory_ActorComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidget> inventoryAsset(TEXT("WidgetBlueprint'/Game/Blueprint/Widgets/WB_Inventory.WB_Inventory_C'"));

	if (inventoryAsset.Succeeded())
	{
		inventoryClass = inventoryAsset.Class;
	}
}


void UInventory_ActorComponent::BeginPlay()
{
	Super::BeginPlay();

	if (inventoryClass != nullptr)
	{
		inventoryWidget = Cast<UInventory_Widget>(CreateWidget<UUserWidget>(GetWorld(), inventoryClass));
		if (inventoryWidget != nullptr)
		{
			inventoryWidget->AddToViewport();
			inventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}


void UInventory_ActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UInventory_ActorComponent::AddItem(FItemData& inItem)
{
	int index = FindSameItem(inItem);

	inventoryWidget->AddSlotToItem(inItem);

	if (index == -1)
	{
		FItemData NewItemData = inItem;
		NewItemData.amount = 1;
		itemDatas.Add(NewItemData);
	}
	else
	{
		++itemDatas[index].amount;
	}
}


void UInventory_ActorComponent::ShowInventory()
{
	if (IsValid(inventoryWidget) == false) return;

	if (isShowInventory == false)
	{
		isShowInventory = true;
		inventoryWidget->SetVisibility(ESlateVisibility::Visible);
		auto playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		playerController->SetShowMouseCursor(true);
		FInputModeGameAndUI inputMode;
		inputMode.SetWidgetToFocus(inventoryWidget->TakeWidget());
		inputMode.SetHideCursorDuringCapture(false);
		playerController->SetInputMode(FInputModeGameAndUI(inputMode));
	}
	else
	{
		isShowInventory = false;
		auto playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		playerController->SetShowMouseCursor(false);
		playerController->SetInputMode(FInputModeGameOnly());
		inventoryWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}


int UInventory_ActorComponent::FindSameItem(FItemData& inItemData)
{
	for (int i = 0; i < itemDatas.Num(); ++i)
	{
		if (itemDatas[i] == inItemData) return i;
	}

	return -1;
}


TArray<FItemData> UInventory_ActorComponent::GetItemDatas()
{
	return itemDatas;
}