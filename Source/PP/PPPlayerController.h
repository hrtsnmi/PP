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
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable, Category = "PC|UI")
		void SetupGameUI();

	UFUNCTION() void ToggleInGameMenu();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PC|Config")
		UPongGameInstance* PongGameInstance;

	UFUNCTION(BlueprintCallable, Category = "Player|Movement") void MoveInput(float Value);
};
