// Copyright Epic Games, Inc. All Rights Reserved.


#include "PacmanGameModeBase.h"

EGameState APacmanGameModeBase::GetCurrentState() const
{
	return CurrentState;
}

void APacmanGameModeBase::SetCurrentState(EGameState InState)
{
	CurrentState = InState;
}
