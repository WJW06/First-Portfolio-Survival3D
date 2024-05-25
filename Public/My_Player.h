#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "My_Player.generated.h"

UCLASS()
class SURVIVAL3D_API AMy_Player : public ACharacter
{
	GENERATED_BODY()
public:
	AMy_Player();
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	FORCEINLINE bool GetIsCrouch() { return isCrouch; }
	FORCEINLINE bool GetIsJump() { return isJump; }
public:
	void ChangeView();
private:
	void SmoothView();
private:
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		class USpringArmComponent* springArmCamera;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		class UCameraComponent* cameraComp;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		class APlayerCameraManager* cameraManager;
	UPROPERTY(VisibleAnywhere, Category = "Camera")
		FName cameraSocket = TEXT("Camera_Socket");
public:
	bool isRun;
	bool isJump;
	bool isCrouch;
	bool isOneView;
	bool isSmoothView;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
		class UActorComponent_Inventory* inventoryComponent;
};