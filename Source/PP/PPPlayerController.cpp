// Fill out your copyright notice in the Description page of Project Settings.


#include "PPPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "PongGameInstance.h"
#include "Camera/CameraActor.h"
#include "Interfaces/PlatformMovementInterface.h"

void APPPlayerController::BeginPlay()
{
	Super::BeginPlay();

	PongGameInstance = GetGameInstance<UPongGameInstance>();

	SetupGameUI();
}

void APPPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APPPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("InGameMenu", IE_Pressed, this, &APPPlayerController::ToggleInGameMenu);
	InputComponent->BindAxis("MovePlatform", this, &APPPlayerController::MoveInput);
}

void APPPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TArray<AActor*> Cameras;
	UGameplayStatics::GetAllActorsOfClass(this, ACameraActor::StaticClass(), Cameras);
	if (Cameras.Num() > 0 && Cameras[0]->IsValidLowLevel())
	{
		SetViewTargetWithBlend(Cameras[0]);
	}
}

void APPPlayerController::SetupGameUI_Implementation()
{
	if (PongGameInstance && PongGameInstance->IsValidLowLevel())
	{
		PongGameInstance->LoadActiveHUDWidget();
	}
}

void APPPlayerController::ToggleInGameMenu()
{
	if(PongGameInstance && PongGameInstance->IsValidLowLevel())
	{
		PongGameInstance->LoadInGameMenuWidget();
	}
}

void APPPlayerController::MoveInput(float Value)
{
	if (GetPawn() && GetPawn()->GetClass()->ImplementsInterface(UPlatformMovementInterface::StaticClass()))
	{
		IPlatformMovementInterface::Execute_Move(GetPawn(), Value);
	}
}
