// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PPPlayerController.generated.h"

/**
 * 
 */
class UPongGameInstance;

UCLASS()
class PP_API APPPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;
	virtual void OnPosses(APawn* InPawn) override;

	UFUNTION(Client, Reliable, BlueprintCallable, Category = "PC|UI")
		void SetupGameUI();

	UFUNTION()
		void ToggleInGameMenu();

	UPROPERTY(, Category = "PC|Config")
		UPongGameInstance* PongGameInstance;

};
