// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameInstance.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "GameFramework/GameUserSettings.h"

DEFINE_LOG_CATEGORY(LogUnrealPong);

const static FName SESSION_NAME = TEXT("UnrealPong Session");
const static FName SERVER_NAME_SETTINGS_KEY = TEXT("UnrealPong Server");

void UPongGameInstance::CreateSession() const
{
	if (SessionInterface.IsValid())
	{
		FOnlineSessionSettings Settings;
		Settings.bIsLANMatch = true;
		Settings.NumPublicConnections = 2;
		Settings.bShouldAdvertise = true;
		Settings.bUsesPresence = true;
		Settings.Set(SERVER_NAME_SETTINGS_KEY, ServerData.Name,
			EOnlineDataAdvertisementType::ViaOnlineServiceAndPing);

		SessionInterface->CreateSession(0, SESSION_NAME, Settings);
	}
}

void UPongGameInstance::OnCreateSessionComplete(const FName SessionName, bool bSuccess)
{
	if (!bSuccess)
	{
		UE_LOG(LogUnrealPong, Warning, TEXT("Could not create session"))
			return;
	}

	if (!ensure(MainMenu))
	{
		return;
	}
	MainMenu->Teardown();
	
	UEngine* Engine = GetEngine();
	if (!ensure(Engine))
	{
		return;
	}
	

	UE_LOG(LogUnrealPong, Log, TEXT("Hosting %s"), *ServerData.Name);

	StartGame();
}

void UPongGameInstance::OnDestroySessionComplete(const FName SessionName, bool bSuccess)
{
	if (bSuccess)
	{
		CreateSession();
		UE_LOG(LogUnrealPong, Log, TEXT("Destroyed existing session"))
	}
	else
	{
		UE_LOG(LogUnrealPong, Warning, TEXT("Could not destroy existing session"))
	}
}

void UPongGameInstance::OnFindSessionsComplete(bool bSuccess)
{
	if (bSuccess && SessionSearch.IsValid())
	{
		UE_LOG(LogUnrealPong, Log, TEXT("Finished Find Session"))

			TArray<FPPServerDataStruct> ServerNames;
		for (FOnlineSessionSearchResult const& Result : SessionSearch->SearchResults)
		{
			UE_LOG(LogUnrealPong, Log, TEXT("Found session names: %s"), *Result.GetSessionIdStr());

			FPPServerDataStruct Data;
			Data.PlayersAmount = 2 - Result.Session.NumOpenPublicConnections - Result.Session.
				NumOpenPrivateConnections;
			UE_LOG(LogUnrealPong, Log, TEXT("Open public connections: %d"), Result.Session.NumOpenPublicConnections);

			Data.HostUsername = Result.Session.OwningUserName;
			FString ServerName;
			if (Result.Session.SessionSettings.Get(SERVER_NAME_SETTINGS_KEY, ServerName))
			{
				Data.Name = ServerName;
			}
			else
			{
				Data.Name = "Could not find name.";
			}
			ServerNames.Add(Data);
		}

		MainMenu->SetServerList(ServerNames);
	}
}

void UPongGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
	if (!SessionInterface.IsValid()) return;

	FString Address;
	if (!SessionInterface->GetResolvedConnectString(SessionName, Address))
	{
		UE_LOG(LogUnrealPong, Warning, TEXT("Could not get connect string."))
			return;
	}

	UEngine* Engine = GetEngine();
	if (!ensure(Engine)) return;

	UE_LOG(LogUnrealPong, Log, TEXT("Joining %s"), *Address)

		APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController)) return;

	PlayerController->ClientTravel(Address, TRAVEL_Absolute);
}

void UPongGameInstance::OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
	LoadMainMenu();
}

void UPongGameInstance::Init()
{
	if (GEngine)
	{
		UGameUserSettings* UserSettings = GEngine->GetGameUserSettings();
		if (UserSettings)
		{
			UserSettings->SetScreenResolution(UserSettings->GetDesktopResolution());
			UserSettings->SetFullscreenMode(EWindowMode::WindowedFullscreen);

			UserSettings->LoadSettings(false);

			UserSettings->ApplySettings(false);
		}
	}

	/** Initialize the Online Subsystem */
	IOnlineSubsystem* Subsystem = IOnlineSubsystem::Get();
	if (Subsystem)
	{
		UE_LOG(LogUnrealPong, Log, TEXT("Found subsystem %s"), *IOnlineSubsystem::Get()->GetSubsystemName().ToString())
			SessionInterface = Subsystem->GetSessionInterface();
		if (SessionInterface.IsValid())
		{
			SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(
				this, &UPongGameInstance::OnCreateSessionComplete);
			SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(
				this, &UPongGameInstance::OnDestroySessionComplete);
			SessionInterface->OnFindSessionsCompleteDelegates.
				AddUObject(this, &UPongGameInstance::OnFindSessionsComplete);
			SessionInterface->OnJoinSessionCompleteDelegates.
				AddUObject(this, &UPongGameInstance::OnJoinSessionComplete);
		}
	}
	else
	{
		UE_LOG(LogUnrealPong, Warning, TEXT("Absent subsystem"))
	}

	if (GEngine)
	{
		GEngine->OnNetworkFailure().AddUObject(this, &UPongGameInstance::OnNetworkFailure);
	}
}

void UPongGameInstance::Host(const FString& ServerName)
{
	if (SessionInterface.IsValid())
	{
		ServerData.Name = ServerName;
		
		const FNamedOnlineSession* ExistingSession = SessionInterface->GetNamedSession(SESSION_NAME);
		if (ExistingSession)
		{
			SessionInterface->DestroySession(SESSION_NAME);
		}
		else
		{
			CreateSession();
		}
	}
}

void UPongGameInstance::Join(const int& Index, const FPPServerDataStruct& InServerData)
{
	if (!SessionInterface.IsValid())
	{
		return;
	}

	if (!SessionSearch.IsValid())
	{
		return;
	}

	if (!ensure(MainMenu))
	{
		return;
	}
	MainMenu->Teardown();

	ServerData.Name = InServerData.Name;
	ServerData.PlayersAmount = InServerData.PlayersAmount;
	ServerData.HostUsername = InServerData.HostUsername;

	SessionInterface->JoinSession(0, SESSION_NAME, SessionSearch->SearchResults[Index]);
}

void UPongGameInstance::StartGame()
{
	if (!ensure(MainMenu))
	{
		return;
	}
	MainMenu->Teardown();

	UEngine* Engine = GetEngine();
	if (!ensure(Engine))
	{
		return;
	}

	UE_LOG(LogUnrealPong, Log, TEXT("Starting Game"));

	UWorld* World = GetWorld();
	if (!ensure(World))
	{
		return;
	}

	//ShowLoadingScreen();

	World->ServerTravel("/Game/Levels/Main?listen");
}

void UPongGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();

	if (!ensure(PlayerController))
	{
		return;
	}

	PlayerController->ClientTravel("/Game/Levels/MainMenu?listen", TRAVEL_Absolute);
}

void UPongGameInstance::RefreshServerList()
{
	SessionSearch = MakeShareable(new FOnlineSessionSearch());
	if (SessionSearch.IsValid())
	{
		SessionSearch->MaxSearchResults = 100;
		SessionSearch->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		
		UE_LOG(LogUnrealPong, Log, TEXT("Starting Find Session"));

		SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
	}
}

void UPongGameInstance::LoadMainMenuWidget()
{
	if (!ensure(MainMenuClass))
	{
		return;
	}

	if (!MainMenu)
	{
		MainMenu = CreateWidget<UMainMenu>(this, MainMenuClass);
	}

	if (!ensure(MainMenu))
	{
		return;
	}

	MainMenu->Setup();
	MainMenu->SetMenuInterface(this);
}

void UPongGameInstance::LoadActiveHUDWidget()
{
	if (!ensure(GameHUDClass))
	{
		return;
	}

	if (!GameHUD)
	{
		GameHUD = CreateWidget<UActiveHUD>(this, GameHUDClass);
	}

	if (!ensure(GameHUD))
	{
		return;
	}

	GameHUD->Setup();
	GameHUD->SetMenuInterface(this);
}

void UPongGameInstance::LoadInGameMenuWidget()
{
	if (!ensure(InGameMenuClass))
	{
		return;
	}

	if (InGameMenu && InGameMenu->IsInViewport())
	{
		InGameMenu->Teardown();
		return;
	}
	
	if (!InGameMenu)
	{
		InGameMenu = CreateWidget<UInGameMenu>(this, InGameMenuClass);
	}

	if (!ensure(InGameMenu))
	{
		return;
	}

	InGameMenu->Setup();
	InGameMenu->SetMenuInterface(this);
}
