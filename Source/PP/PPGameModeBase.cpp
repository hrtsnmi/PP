// Copyright Epic Games, Inc. All Rights Reserved.


#include "PPGameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "PlatformPawn.h"
#include "BallActor.h"

void APPGameModeBase::StartGame() const
{
	TArray<AActor*> Balls;
	UGameplayStatics::GetAllActorsOfClass(this, ABallActor::StaticClass(), Balls);
	if (Balls.Num() > 0 && IsValid(Balls[0]))
	{
		Cast<ABallActor>(Balls[0])->Start();
	}
}

void APPGameModeBase::EndGame()
{
	TArray<AActor*> Balls;
	UGameplayStatics::GetAllActorsOfClass(this, ABallActor::StaticClass(), Balls);
	if (Balls.Num() > 0 && IsValid(Balls[0]))
	{
		Cast<ABallActor>(Balls[0])->GameOver();
	}
}

void APPGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	TArray<AActor*> Pawns;
	UGameplayStatics::GetAllActorsOfClass(this, APlatformPawn::StaticClass(), Pawns);
	if (Pawns.Num() > 0)
	{
		for (AActor* Pawn : Pawns)
		{
			APlatformPawn* PlatforPlayer = Cast<APlatformPawn>(Pawn);
			if (PlatforPlayer && !PlatforPlayer->IsPawnControlled())
			{
				NewPlayer->Possess(PlatforPlayer);
				PlatforPlayer->SetOwner(NewPlayer);
			}
		}
	}

	if (GetNumPlayers() == 2)
	{
		StartGame();
	}
}

void APPGameModeBase::Logout(AController* Existing)
{
	EndGame();

	UWorld* World = GetWorld();
	if(!ensure(World))
	{
		return;
	}

	World->ServerTravel("/Game/Maps/Main?listen");
	Super::Logout(Existing);
}
