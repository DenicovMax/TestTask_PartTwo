// Copyright Epic Games, Inc. All Rights Reserved.

#include "TT/Core/Public/TTGameMode.h"
#include "TT/Character/Public/TTCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATTGameMode::ATTGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
