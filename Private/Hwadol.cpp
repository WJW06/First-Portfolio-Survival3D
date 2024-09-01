#include "Hwadol.h"

AHwadol::AHwadol()
{
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> meshAsset(TEXT(""));

	if (meshAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(meshAsset.Object);
		GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
		GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));
	}
}