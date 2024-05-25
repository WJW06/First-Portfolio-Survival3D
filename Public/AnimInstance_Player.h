// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "My_Player.h"
#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstance_Player.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVAL3D_API UAnimInstance_Player : public UAnimInstance
{
	GENERATED_BODY()
public:
	UAnimInstance_Player();
protected:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
		float currentSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
		float direction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
		float pitch;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
		bool isCrouch;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
		bool isJump;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Player", meta = (AllowPrivateAccess = "true"))
		class AMy_Player* my_player;
};
