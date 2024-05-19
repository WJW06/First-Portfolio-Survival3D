#include "ActorComponent_Inventory.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

UActorComponent_Inventory::UActorComponent_Inventory()
{
	PrimaryComponentTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidget> inventoryAsset(TEXT(""));

	if (inventoryAsset.Succeeded())
	{
		inventoryClass = inventoryAsset.Class;
	}
}



void UActorComponent_Inventory::BeginPlay()
{
	Super::BeginPlay();

	if (inventoryClass != nullptr)
	{
		//inventoryWidget = Cast<>(CreateWidget<UUserWidget>(GetWorld(), inventoryClass));
		//if (inventoryWidget != nullptr)
		//{
		//	inventoryWidget->AddToViewport();
		//	inventoryWidget->SetVisibility(ESlateVisibility::Hidden);
		//}
	}
}


void UActorComponent_Inventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UActorComponent_Inventory::AddItem(FItemData& inItem)
{
	//int index = FindSameItem(inItem);

	//inventoryWidget->AddSlotToItem(inItem);

	//if (index == -1)
	//{
	//	FItemData NewItemData = inItem;
	//	NewItemData.amount = 1;
	//	itemDatas.Add(NewItemData);
	//}
	//else
	//{
	//	++itemDatas[index].amount;
	//}
}

void UActorComponent_Inventory::ShowInventory()
{
	//if (IsValid(inventoryWidget) == false) return;

	//if (isShowInventory == false)
	//{
	//	isShowInventory = true;
	//	inventoryWidget->SetVisibility(ESlateVisibility::Visible);
	//	auto playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//	playerController->SetShowMouseCursor(true);
	//	FInputModeGameAndUI inputMode;
	//	inputMode.SetWidgetToFocus(inventoryWidget->TakeWidget());
	//	inputMode.SetHideCursorDuringCapture(false);
	//	playerController->SetInputMode(FInputModeGameAndUI(inputMode));
	//}
	//else
	//{
	//	isShowInventory = false;
	//	auto playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//	playerController->SetShowMouseCursor(false);
	//	playerController->SetInputMode(FInputModeGameAndUI());
	//	inventoryWidget->SetVisibility(ESlateVisibility::Hidden);
	//}
}

int UActorComponent_Inventory::FindSameItem(FItemData& inItemData)
{
	for (int i = 0; i < itemDatas.Num(); ++i)
	{
		if (itemDatas[i] == inItemData) return i;
	}

	return -1;
}

TArray<FItemData> UActorComponent_Inventory::GetItemDatas()
{
	return itemDatas;
}