#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "My_PlayerController.generated.h"

UCLASS()
class SURVIVAL3D_API AMy_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AMy_PlayerController();
protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;
private:
	UFUNCTION()
		void MoveForward(float value);
	UFUNCTION()
		void MoveRight(float value);
	UFUNCTION()
		void OnRun();
	UFUNCTION()
		void OffRun();
	UFUNCTION()
		void OnCrouch();
	UFUNCTION()
		void OffCrouch();
	UFUNCTION()
		void OnChangeView();
	UFUNCTION()
		void OnInventory();
private:
	UPROPERTY(VisibleAnywhere, Category = "Player")
		class AMy_Player* my_player;
};
