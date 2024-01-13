// Fill out your copyright notice in the Description page of Project Settings.


#include "PPGameState.h"
#include "PongGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "PPGameModeBase.h"
#include "PPPlayerState.h"
#include "Net/UnrealNetwork.h"

void APPGameState::RestartGame_Implementation()
{
	int PlayersReady{};

	for (APlayerState* PlayerState: PlayerArray)
	{
		APPPlayerState* PPPlayerState = Cast<APPPlayerState>(PlayerState);
		if (PPPlayerState)
		{
			PlayersReady++;
		}
	}

	if (PlayersReady == 2)
	{
		bGameOver = true;
		RedPlayerScore = 0;
		BluePlayerScore = 0;

		for (APlayerState* PlayerState : PlayerArray)
		{
			APPPlayerState* PPPlayerState = Cast<APPPlayerState>(PlayerState);
			if (PPPlayerState)
			{
				PPPlayerState->SetPlayAgain(false);
			}
		}

		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
		if (GameMode)
		{
			APPGameModeBase* PPGameMode = Cast<APPGameModeBase>(GameMode);
			if (PPGameMode)
			{
				PPGameMode->StartGame();
			}
		}
	}
}

void APPGameState::IncrementScoreAtPlayerID_Implementation(int ID)
{
	if (ID == 1)
	{
		RedPlayerScore++;
	}
	else if(ID == 2)
	{
		BluePlayerScore++;
	}
	else
	{
		//UE_LOG(LogPongClone, Warning, TEXT("ID is not set on PongGate"));
	}

	if (RedPlayerScore == WinScore || BluePlayerScore == WinScore)
	{
		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(this);
		if (GameMode)
		{
			APPGameModeBase* PPGameMode = Cast<APPGameModeBase>(GameMode);
			if(PPGameMode)
			{
				bGameOver = true;
				PPGameMode->EndGame();
			}
		}
	}
}

void APPGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APPGameState, RedPlayerScore);
	DOREPLIFETIME(APPGameState, BluePlayerScore);
	DOREPLIFETIME(APPGameState, bGameOver);
}
