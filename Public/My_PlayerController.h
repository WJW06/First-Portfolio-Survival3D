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
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;
private:
	UFUNCTION()
		void MoveForward(float value);
	UFUNCTION()
		void MoveRight(float value);
	UFUNCTION()
		void LookMouseCursor();
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
