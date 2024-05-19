// Fill out your copyright notice in the Description page of Project Settings.


#include "APlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AAPlayer::AAPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> meshAsset(TEXT("SkeletalMesh'/Game/Asset/Man/Mesh/Full/SK_Man_Full_04.SK_Man_Full_04'"));
	
	if (meshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(meshAsset.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> animAsset(TEXT("AnimBlueprint'/Game/Blueprint/Player/ABP_Player.ABP_Player_C'"));

	if (animAsset.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(animAsset.Class);
	}

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->JumpZVelocity = 400.f;

	springArmCamera = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmCamera"));
	springArmCamera->SocketOffset = FVector(0, 0, 0);
	springArmCamera->TargetArmLength = 250.f;
	springArmCamera->bDoCollisionTest = true;
	springArmCamera->bUsePawnControlRotation = true;
	springArmCamera->SetupAttachment(RootComponent);
	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	cameraComp->SetupAttachment(springArmCamera);

	Tags.Add(FName(TEXT("Player")));
}

void AAPlayer::BeginPlay()
{
	Super::BeginPlay();

}

void AAPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	springArmCamera->SetWorldLocation(GetMesh()->GetSocketLocation(cameraSocket));
}

void AAPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AAPlayer::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AAPlayer::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction(TEXT("Run"), IE_Pressed, this, &AAPlayer::OnRun);
	PlayerInputComponent->BindAction(TEXT("Run"), IE_Released, this, &AAPlayer::OffRun);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &AAPlayer::OnCrouch);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &AAPlayer::OffCrouch);
	PlayerInputComponent->BindAction(TEXT("ChangeView"), IE_Pressed, this, &AAPlayer::ChangeView);
}

void AAPlayer::MoveForward(float value)
{
	FRotator YawRot = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FQuat(YawRot).GetForwardVector().GetUnsafeNormal2D();
	AddMovementInput(Direction, value);
}

void AAPlayer::MoveRight(float value)
{
	FRotator YawRot = FRotator(0, GetControlRotation().Yaw, 0);
	FVector Direction = FQuat(YawRot).GetRightVector().GetUnsafeNormal2D();
	AddMovementInput(Direction, value);
}

void AAPlayer::OnRun()
{
	isRun = true;
	GetCharacterMovement()->MaxWalkSpeed += 200.f;
}

void AAPlayer::OffRun()
{
	isRun = false;
	GetCharacterMovement()->MaxWalkSpeed -= 200.f;
}

void AAPlayer::OnCrouch()
{
	isCrouch = true;
	GetCharacterMovement()->MaxWalkSpeed -= 100.f;
	GetCharacterMovement()->JumpZVelocity = 0.f;
}

void AAPlayer::OffCrouch()
{
	isCrouch = false;
	GetCharacterMovement()->MaxWalkSpeed += 100.f;
	GetCharacterMovement()->JumpZVelocity = 400.f;
}

void AAPlayer::ChangeView()
{
	isOneView = !isOneView;

	if (isOneView)
	{
		springArmCamera->TargetArmLength = 0.f;
		springArmCamera->bDoCollisionTest = false;
	}
	else
	{
		springArmCamera->TargetArmLength = 250.f;
		springArmCamera->bDoCollisionTest = true;
	}
}

