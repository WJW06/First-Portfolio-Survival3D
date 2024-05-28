#pragma once

#include "ItemData.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorComponent_Inventory.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SURVIVAL3D_API UActorComponent_Inventory : public UActorComponent
{
	GENERATED_BODY()
public:	
	UActorComponent_Inventory();
protected:
	virtual void BeginPlay() override;
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:
	void AddItem(struct FItemData& inItem);
	void ShowInventory();
	int FindSameItem(struct FItemData& inItemData);
	UFUNCTION()
		TArray<FItemData> GetItemDatas();
private:
	UPROPERTY(VisibleAnywhere, Category = "Item")
		TArray<FItemData> itemDatas;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = true))
		TSubclassOf<class UUserWidget> inventoryClass;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Inventory", meta = (AllowPrivateAccess = true))
		class UWidget_Inventory* inventoryWidget;

	bool isShowInventory = false;
};
