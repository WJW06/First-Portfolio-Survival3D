#include "My_PlayerController.h"
#include "My_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ActorComponent_Inventory.h"

AMy_PlayerController::AMy_PlayerController()
{

}

void AMy_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (IsValid(InPawn) == false) return;

	my_player = Cast<AMy_Player>(InPawn);
}

void AMy_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis(TEXT("MoveForward"), this, &AMy_PlayerController::MoveForward);
	InputComponent->BindAxis(TEXT("MoveRight"), this, &AMy_PlayerController::MoveRight);
	InputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &AMy_PlayerController::OnRun);
	InputComponent->BindAction(TEXT("Run"), IE_Released, this, &AMy_PlayerController::OffRun);
	InputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &AMy_PlayerController::OnCrouch);
	InputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &AMy_PlayerController::OffCrouch);
	InputComponent->BindAction(TEXT("ChangeView"), IE_Pressed, this, &AMy_PlayerController::OnChangeView);
	InputComponent->BindAction(TEXT("Inventory"), IE_Pressed, this, &AMy_PlayerController::OnInventory);
}


void AMy_PlayerController::MoveForward(float value)
{
	if (value != 0.f)
	{
		const FRotator YawRot = FRotator(0, GetControlRotation().Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		my_player->AddMovementInput(Direction, value);
	}
}

void AMy_PlayerController::MoveRight(float value)
{
	if (value != 0.f)
	{
		const FRotator YawRot = FRotator(0, GetControlRotation().Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
		my_player->AddMovementInput(Direction, value);
	}
}

void AMy_PlayerController::OnRun()
{
	my_player->isRun = true;
	my_player->GetCharacterMovement()->MaxWalkSpeed += 200.f;
}

void AMy_PlayerController::OffRun()
{
	my_player->isRun = false;
	my_player->GetCharacterMovement()->MaxWalkSpeed -= 200.f;
}

void AMy_PlayerController::OnCrouch()
{
	my_player->isCrouch = true;
	my_player->GetCharacterMovement()->MaxWalkSpeed -= 100.f;
	my_player->GetCharacterMovement()->JumpZVelocity = 0.f;
}

void AMy_PlayerController::OffCrouch()
{
	my_player->isCrouch = false;
	my_player->GetCharacterMovement()->MaxWalkSpeed += 100.f;
	my_player->GetCharacterMovement()->JumpZVelocity = 400.f;
}

void AMy_PlayerController::OnChangeView()
{
	my_player->ChangeView();
}

void AMy_PlayerController::OnInventory()
{
	my_player->inventoryComponent->ShowInventory();
}