#pragma once

#include "ItemData.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class SURVIVAL3D_API AItem : public AActor
{
	GENERATED_BODY()
	
public:
	AItem();
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
public:
	FORCEINLINE FItemData& GetItemData()
	{
		return itemData;
	}
	FORCEINLINE void SetItemData(FItemData& inItemData)
	{
		itemData = inItemData;
	}
protected:
	virtual void NotifyActorBeginOverlap(class AActor* OtherActor) override;
public:
	virtual void OnConstruction(const FTransform& Transform) override;
	void SetItemRowName(FName inItemName);
private:
	UPROPERTY(EditAnywhere, Category = "Item")
		struct FDataTableRowHandle itemRowHandle;
	UPROPERTY(EditAnywhere, Category = "Item")
		struct FItemData itemData;
	UPROPERTY(EditAnywhere, Category = "Item")
		class USkeletalMeshComponent* itemMesh;
	UPROPERTY(EditAnywhere, Category = "Item")
		class USphereComponent* collision;
};
