#include "My_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

AMy_Player::AMy_Player()
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

void AMy_Player::BeginPlay()
{
	Super::BeginPlay();

}

void AMy_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isSmoothView) SmoothView();

	springArmCamera->SetWorldLocation(GetMesh()->GetSocketLocation(cameraSocket));
}

void AMy_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
}

void AMy_Player::ChangeView()
{
	if (isSmoothView) return;

	isOneView = !isOneView;
	isSmoothView = true;

	if (isOneView) springArmCamera->bDoCollisionTest = false;
	else springArmCamera->bDoCollisionTest = true;
}

void AMy_Player::SmoothView()
{
	if (isOneView && springArmCamera->TargetArmLength > 0.f)
	{
		springArmCamera->TargetArmLength -= 25.f;
	}
	else if (!isOneView && springArmCamera->TargetArmLength < 250.f)
	{
		springArmCamera->TargetArmLength += 25.f;
	}
	else isSmoothView = false;
}
