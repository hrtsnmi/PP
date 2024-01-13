// Fill out your copyright notice in the Description page of Project Settings.


#include "PPPlayerState.h"
#include "PPGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

void APPPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APPPlayerState, bPlayAgain);
}

void APPPlayerState::SetPlayAgain_Implementation(bool bInPlayAgain)
{
	bPlayAgain = bInPlayAgain;

	AGameStateBase* GameState = UGameplayStatics::GetGameState(this);
	if (GameState)
	{
		APPGameState* PPGameState = Cast<APPGameState>(GameState);
		if (PPGameState)
		{
			PPGameState->RestartGame();
		}
	}
}
