#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "APlayer.generated.h"

UCLASS()
class SURVIVAL3D_API AAPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	AAPlayer();

protected:
	virtual void BeginPlay() override;
public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
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
		void ChangeView();
public:
	FORCEINLINE bool GetIsCrouch() { return isCrouch; }
	FORCEINLINE bool GetIsJump() { return isJump; }
private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		class USpringArmComponent* springArmCamera;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		class UCameraComponent* cameraComp;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		class APlayerCameraManager* cameraManager;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		FName cameraSocket = TEXT("Camera_Socket");
private:
	bool isRun;
	bool isJump;
	bool isCrouch;
	bool isOneView;
};
