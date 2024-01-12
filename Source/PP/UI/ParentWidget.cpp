// Fill out your copyright notice in the Description page of Project Settings.


#include "ParentWidget.h"

void UParentWidget::Setup()
{
	this->AddToViewport();

	const UWorld* Word = GetWorld();
	if(!ensure(Word))
	{
		return;
	}

	APlayerController* PlayerController = Word->GetFirstPlayerController();
	if (!ensure(PlayerController))
	{
		return;
	}

	this->SetOwningPlayer(PlayerController);

	FInputModeGameAndUI InputModeData;
	InputModeData.SetWidgetToFocus(this->TakeWidget());
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = true;
}

void UParentWidget::Teardown()
{
	this->RemoveFromViewport();

	const UWorld* Word = GetWorld();
	if (!ensure(Word))
	{
		return;
	}

	APlayerController* PlayerController = Word->GetFirstPlayerController();
	if (!ensure(PlayerController))
	{
		return;
	}

	FInputModeGameAndUI InputModeData;
	PlayerController->SetInputMode(InputModeData);
	PlayerController->bShowMouseCursor = false;
}

void UParentWidget::SetMenuInterface(IMenuInterface* InIMenuInterface)
{
	MenuInterface = InIMenuInterface;
}
