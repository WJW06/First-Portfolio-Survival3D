// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance_Player.h"
#include "GameFramework/CharacterMovementComponent.h"

UAnimInstance_Player::UAnimInstance_Player() : currentSpeed(0)
{

}

void UAnimInstance_Player::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	my_player = Cast<AMy_Player>(TryGetPawnOwner());
}

void UAnimInstance_Player::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (IsValid(my_player))
	{
		currentSpeed = my_player->GetVelocity().Size2D();
		FRotator yawDirection = FRotator(0, my_player->GetControlRotation().Yaw, 0);
		direction = CalculateDirection(my_player->GetVelocity(), yawDirection);
		pitch = my_player->GetBaseAimRotation().Pitch;
		isCrouch = my_player->GetIsCrouch();
		isJump = my_player->GetMovementComponent()->IsFalling();
	}
}
