// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/SphereComponent.h"
#include "My_Player.h"
#include "ActorComponent_Inventory.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> DataAsset(TEXT("DataTable'/Game/DataTable/DT_ItemData.DT_ItemData'"));

	if (DataAsset.Succeeded())
	{
		itemRowHandle.DataTable = DataAsset.Object;
		itemRowHandle.RowName = TEXT("Sword");
	}

	itemMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ItemMesh"));
	itemMesh->SetCollisionProfileName(FName(TEXT("Item")));
	itemMesh->SetSimulatePhysics(true);
	RootComponent = itemMesh;
	Tags.Add(FName(TEXT("Item")));

	collision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	collision->AttachToComponent(itemMesh, FAttachmentTransformRules::KeepRelativeTransform);
	collision->InitSphereRadius(100.f);
}

void AItem::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AMy_Player* player = Cast<AMy_Player>(OtherActor);
	if (IsValid(player))
	{
		if (player->inventoryComponent != nullptr)
		{
			player->inventoryComponent->AddItem(itemData);
			Destroy();
		}
	}
}

void AItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	itemData = *itemRowHandle.DataTable->FindRow<FItemData>(itemRowHandle.RowName, "");

	if (&itemData != nullptr && itemMesh != nullptr)
	{
		itemMesh->SetSkeletalMesh(itemData.itemMesh);
		if (itemData.itemType == EItemType::Item_Equipment) itemMesh->SetRelativeScale3D(FVector(0.3f));
		else itemMesh->SetRelativeScale3D(FVector(0.5f));
	}
}

void AItem::SetItemRowName(FName inItemName)
{
	FString itemName = inItemName.ToString();
	FName rowName;
	if (itemName.Contains("Sword"))
	{
		rowName = TEXT("Sword");
	}
	else if (itemName.Contains("Dagger"))
	{
		rowName = TEXT("Dagger");
	}
	else if (itemName.Contains("Bow"))
	{
		rowName = TEXT("Bow");
	}
	else
	{
		rowName = inItemName;
	}
	itemRowHandle.RowName = rowName;
}