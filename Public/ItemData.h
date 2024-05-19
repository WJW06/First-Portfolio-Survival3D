#pragma once

#include "Engine/DataTable.h"
#include "CoreMinimal.h"
#include "ItemData.generated.h"

UENUM(BlueprintType, meta = (ToolTip = "ItemType"))
enum class EItemType : uint8
{
	Item_None UMETA(DisplayName = "None"),
	Item_Equipment UMETA(DisplayName = "Equipment"),
	Item_Useable UMETA(DisplayName = "Useable"),
	Item_Etc  UMETA(DisplayName = "Etc")
};

USTRUCT(Atomic, BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	bool operator ==(const FItemData& inItemData) const
	{
		bool isName = (itemName == inItemData.itemName);
		bool isType = (itemType == inItemData.itemType);
		bool isPrice = (price == inItemData.price);
		bool isMesh = (itemMesh == inItemData.itemMesh);
		bool isIcon = (icon == inItemData.icon);

		return (isName && isType && isPrice && isMesh && isIcon);
	}

	bool operator !=(const FItemData& inItemData) const
	{
		return !(*this == inItemData);
	}
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName itemName = FName(TEXT(""));
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		EItemType itemType = EItemType::Item_None;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USkeletalMesh* itemMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UTexture2D* icon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int amount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int price = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString description = FString(TEXT(""));
};