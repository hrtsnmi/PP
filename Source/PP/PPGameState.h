// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PPGameState.generated.h"

/**
 * 
 */
UCLASS()
class PP_API APPGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(Server, Reliable, BlueprintCallable)
		void RestartGame();

	UFUNCTION(Server, Reliable, BlueprintCallable)
		void IncrementScoreAtPlayerID(int ID);

	int GetRedPlayerScore() const { return RedPlayerScore; }
	int GetBluePlayerScore() const { return BluePlayerScore; }

protected:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Config")
		int RedPlayerScore{};

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Config")
		int BluePlayerScore{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Config")
		int WinScore{ 3 };

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Config")
		bool bGameOver{ false };
};
