// Copyright Epic Games, Inc. All Rights Reserved.


#include "Survival3DGameModeBase.h"
#include "My_Player.h"
#include "My_PlayerController.h"

ASurvival3DGameModeBase::ASurvival3DGameModeBase()
{
	DefaultPawnClass = AMy_Player::StaticClass();
	PlayerControllerClass = AMy_PlayerController::StaticClass();
}