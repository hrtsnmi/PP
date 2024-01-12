// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "../Headers/PPData.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "PPServerRowWidget.h"
#include "../Interfaces/MenuInterface.h"

DEFINE_LOG_CATEGORY(LogUnrealPongUI);

void UMainMenu::SetActiveWidget(const int& Index)
{
	m_Switcher->SetActiveWidgetIndex(Index);
}

void UMainMenu::SetServerList(TArray<FPPServerDataStruct> ServerNames)
{
	const UWorld* World = GetWorld();
	if (!ensure(World))
	{
		return;
	}

	m_ServerList->ClearChildren();

	uint32 i = 0;
	for (FPPServerDataStruct const& ServerData : ServerNames)
	{
		/*UPPServerRowWidget* ServerRow = CreateWidget<UPPServerRowWidget>(World, ServerRowWidgetClass);
		if (!ensure(ServerRow))
		{
			return;
		}

		ServerRow->SetServerData(ServerData);
		ServerRow->Setup(this, i);*/
		++i;

		//m_ServerList->AddChild(ServerRow);
	}
}

void UMainMenu::SelectserverRowIndex(const uint32 Index)
{
	SelectedServerRowIndex = Index;
	UpdateServerRowChildren();
}

bool UMainMenu::Initialize()
{
	const bool bSucces = Super::Initialize();
	
	if (!bSucces)
	{
		return false;
	}

	//bind callbacks
	if(!ensure(m_ButtonHost))
	{
		return false;
	}
	m_ButtonHost->OnClicked.AddDynamic(this, &UMainMenu::HostServer);

	if (!ensure(m_ButtonJoin))
	{
		return false;
	}
	m_ButtonJoin->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);

	if (!ensure(m_ButtonQuit))
	{
		return false;
	}
	m_ButtonQuit->OnClicked.AddDynamic(this, &UMainMenu::QuitPressed);
	


	if (!ensure(m_CancelJoinButton))
	{
		return false;
	}
	m_CancelJoinButton->OnClicked.AddDynamic(this, &UMainMenu::OpenMainMenu);

	if (!ensure(m_RefreshButton))
	{
		return false;
	}
	m_RefreshButton->OnClicked.AddDynamic(this, &UMainMenu::RefreshServerList);

	if (!ensure(m_ConfirmButton))
	{
		return false;
	}
	m_ConfirmButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);

	m_Switcher->SetActiveWidget(m_MainMenu);
	return true;
}

void UMainMenu::UpdateServerRowChildren()
{
	for (size_t i{}; i < m_ServerList->GetChildrenCount(); ++i)
	{
		UPPServerRowWidget* Row = Cast<UPPServerRowWidget>(m_ServerList->GetChildAt(i));
		if (Row)
		{
			//Row->SetrowIsSelected(SelectserverRowIndex.IsSet() && SelectserverRowIndex.GetValue()==i);
		}
	}
}

void UMainMenu::HostServer()
{
	if (MenuInterface)
	{
		MenuInterface->Host("Pong");
	}
}

void UMainMenu::JoinServer()
{
	if (SelectedServerRowIndex.IsSet() && MenuInterface)
	{
		if (const UPPServerRowWidget* Row = Cast<UPPServerRowWidget>(m_ServerList->GetChildAt(SelectedServerRowIndex.GetValue())))
		{
			m_Switcher->SetActiveWidget(m_MainMenu);
			//MenuInterface->Join(SelectedServerRowIndex.GetValue(), Row->GetServerData());
		}
	}
	else
	{
		UE_LOG(LogUnrealPongUI, Warning, TEXT("Selected Index Not Set"));
	}
}

void UMainMenu::QuitPressed()
{
	const UWorld* World = GetWorld();
	if (!ensure(World))
	{
		return;
	}

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController))
	{
		return;
	}

	PlayerController->ConsoleCommand("quit");
}

void UMainMenu::OpenMainMenu()
{
	if (!ensure(m_Switcher))
	{
		return;
	}

	if (!ensure(m_MainMenu))
	{
		return;
	}

	m_Switcher->SetActiveWidget(m_MainMenu);
}

void UMainMenu::OpenJoinMenu()
{
	if (!ensure(m_Switcher))
	{
		return;
	}

	if (!ensure(m_JoinMenu))
	{
		return;
	}

	m_Switcher->SetActiveWidget(m_JoinMenu);

	RefreshServerList();
}

void UMainMenu::RefreshServerList()
{
	if (MenuInterface)
	{
		m_ServerList->ClearChildren();
		MenuInterface->RefreshServerList();
	}
}
