// Copyright Epic Games, Inc. All Rights Reserved.


#include "Survival3DGameModeBase.h"
#include "APlayer.h"

ASurvival3DGameModeBase::ASurvival3DGameModeBase()
{
	DefaultPawnClass = AAPlayer::StaticClass();
}