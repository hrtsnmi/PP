// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include "Components/Button.h"
#include "../Interfaces/MenuInterface.h"

bool UInGameMenu::Initialize()
{
	bool bSucces = Super::Initialize();
	if (!bSucces)
	{
		return false;
	}

	if (!ensure(m_ResumeButton))
	{
		return false;
	}
	m_ResumeButton->OnClicked.AddDynamic(this, &UInGameMenu::ResumePressed);

	if (!ensure(m_LeaveSessionButton))
	{
		return false;
	}
	m_LeaveSessionButton->OnClicked.AddDynamic(this, &UInGameMenu::LeaveGamePressed);

	if (!ensure(m_QuitButton))
	{
		return false;
	}
	m_QuitButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitGamePressed);

	return true;
}

void UInGameMenu::ResumePressed()
{
	Teardown();
}

void UInGameMenu::LeaveGamePressed()
{
	if (MenuInterface)
	{
		Teardown();
		MenuInterface->LoadMainMenu();
	}
}

void UInGameMenu::QuitGamePressed()
{
	APlayerController* OwningPlayerController = GetOwningPlayer();
	if (OwningPlayerController)
	{
		OwningPlayerController->ConsoleCommand("quit");
	}
}
