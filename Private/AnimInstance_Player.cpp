// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance_Player.h"
#include "GameFramework/CharacterMovementComponent.h"

UAnimInstance_Player::UAnimInstance_Player() : currentSpeed(0)
{

}

void UAnimInstance_Player::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	player = Cast<AAPlayer>(TryGetPawnOwner());
}

void UAnimInstance_Player::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (IsValid(player))
	{
		currentSpeed = player->GetVelocity().Size2D();
		FRotator yawDirection = FRotator(0, player->GetControlRotation().Yaw, 0);
		direction = CalculateDirection(player->GetVelocity(), yawDirection);
		pitch = player->GetBaseAimRotation().Pitch;
		isCrouch = player->GetIsCrouch();
		isJump = player->GetMovementComponent()->IsFalling();
	}
}
