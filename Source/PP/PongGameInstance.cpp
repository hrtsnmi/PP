// Fill out your copyright notice in the Description page of Project Settings.


#include "PongGameInstance.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "GameFramework/GameUserSettings.h"

DEFINE_LOG_CATEGORY(LogUnrealPong);

void UPongGameInstance::CreateSession() const
{
}

void UPongGameInstance::OnCreateSessionComplete(const FName SessionName, bool bSuccess)
{
}

void UPongGameInstance::OnDestroySessionComplete(const FName SessionName, bool bSuccess)
{
}

void UPongGameInstance::OnFindSessionsComplete(bool bSuccess)
{
}

void UPongGameInstance::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{
}

void UPongGameInstance::OnNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
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
	
}

void UPongGameInstance::Join(const int& Index, const FPServerData& InServerData)
{
}

void UPongGameInstance::StartGame()
{
}

void UPongGameInstance::LoadMainMenu()
{
}

void UPongGameInstance::RefreshServerList()
{
}
