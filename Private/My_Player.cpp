#include "My_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Inventory_ActorComponent.h"

AMy_Player::AMy_Player()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

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

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->JumpZVelocity = 400.f;

	springArmCamera = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmCamera"));
	springArmCamera->SetupAttachment(RootComponent);
	springArmCamera->bInheritPitch = false;
	springArmCamera->bInheritRoll = false;
	springArmCamera->bInheritYaw = false;
	springArmCamera->TargetArmLength = 800.f;
	springArmCamera->SocketOffset = FVector(0, 0, 0);
	springArmCamera->AddRelativeRotation(FRotator(-80, 0, 0));
	springArmCamera->bDoCollisionTest = false;
	springArmCamera->bUsePawnControlRotation = false; // Fix Camera

	cameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	cameraComp->SetupAttachment(springArmCamera);
	cameraComp->bUsePawnControlRotation = false;

	inventoryComponent = CreateDefaultSubobject<UInventory_ActorComponent>(TEXT("InventoryComponent"));

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

	if (isOneView) springArmCamera->SetWorldLocation(GetMesh()->GetSocketLocation(cameraSocket));
}

void AMy_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	inputComponent = PlayerInputComponent;
	if (isOneView)
	{
		PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
		PlayerInputComponent->BindAxis("Lookup", this, &APawn::AddControllerPitchInput);
	}
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
}

void AMy_Player::ChangeView()
{
	if (isSmoothView) return;

	isOneView = !isOneView;
	isSmoothView = true;
	
	SetupPlayerInputComponent(inputComponent);
}

void AMy_Player::SmoothView()
{
	if (isOneView && springArmCamera->TargetArmLength > 0.f)
	{
		springArmCamera->TargetArmLength -= 25.f;
		if (springArmCamera->TargetArmLength <= 0.f)
		{
			springArmCamera->bUsePawnControlRotation = true; // Fix Camera
		}
	}
	else if (!isOneView && springArmCamera->TargetArmLength < 800.f)
	{
		springArmCamera->TargetArmLength += 25.f;
		springArmCamera->bUsePawnControlRotation = false; // Fix Camera
	}
	else isSmoothView = false;
}
