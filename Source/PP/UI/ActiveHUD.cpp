// Fill out your copyright notice in the Description page of Project Settings.


#include "ActiveHUD.h"
#include "../PPPlayerState.h"
#include "Components/Button.h"
#include "../Interfaces/MenuInterface.h"

bool UActiveHUD::Initialize()
{
	bool bSucces = Super::Initialize();
	if(!bSucces)
	{
		return false;
	}

	if (!ensure(m_CancelButton))
	{
		return false;
	}
	m_CancelButton->OnClicked.AddDynamic(this, &UActiveHUD::QuitGame);

	if (!ensure(m_RefreshButton))
	{
		return false;
	}
	m_RefreshButton->OnClicked.AddDynamic(this, &UActiveHUD::RestartGame);

	return true;
}

void UActiveHUD::RestartGame()
{
	APPPlayerState* PPPlayerState = GetOwningPlayer()->GetPlayerState<APPPlayerState>();
	if (PPPlayerState)
	{
		PPPlayerState->SetPlayAgain(true);
	}
}
	

void UActiveHUD::QuitGame()
{
	if (MenuInterface)
	{
		Teardown();

		MenuInterface->LoadMainMenu();
	}
}
