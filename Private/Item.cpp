// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/SphereComponent.h"
#include "My_Player.h"
//#include "InventoryComponent.h"

AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UDataTable> DataAsset(TEXT(""));

	if (DataAsset.Succeeded())
	{
		itemRowHandle.DataTable = DataAsset.Object;
		itemRowHandle.RowName = TEXT("Sword");
	}

	itemMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ItemMesh"));
	itemMesh->SetCollisionProfileName(FName(TEXT("Item")));
	itemMesh->SetRelativeScale3D(FVector(0.5f));
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
		//if (player->InventoryComponent != nullptr)
		//{
		//	player->InventoryComponent->AddItem(itemData);
		//	Destroy();
		//}
	}
}

void AItem::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	itemData = *itemRowHandle.DataTable->FindRow<FItemData>(itemRowHandle.RowName, "");

	if (&itemData != nullptr && itemMesh != nullptr)
	{
		itemMesh->SetSkeletalMesh(itemData.itemMesh);
	}
}

void AItem::SetItemRowName(FName inItemName)
{
	//ItemRowHandle.RowName = InItemName;
	FName rowName;
	if (inItemName == FName(TEXT("SteelSword")))
	{
		rowName = TEXT("Sword");
	}
	else if (inItemName == FName(TEXT("Advanced Dagger")))
	{
		rowName = TEXT("Dagger");
	}
	else if (inItemName == FName(TEXT("Wind Force")))
	{
		rowName = TEXT("Bow");
	}
	else
	{
		rowName = inItemName;
	}
	itemRowHandle.RowName = rowName;
}