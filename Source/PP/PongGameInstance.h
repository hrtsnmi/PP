// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/MenuInterface.h"
#include "Interfaces/OnlineSessionInterface.h"

#include "PongGameInstance.generated.h"

/**
 * 
 */
DECLARE_LOG_CATEGORY_EXTERN(LogUnrealPong, Log, All);

UCLASS()
class PP_API UPongGameInstance :
	public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()
	
protected:
	/// Variables
	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;
	
	
	void CreateSession() const;

	////////////////////////
	/// Delegate Functions, called by the SessionInterface
	void OnCreateSessionComplete(const FName  SessionName, bool bSuccess);
	void OnDestroySessionComplete(const FName  SessionName, bool bSuccess);
	void OnFindSessionsComplete(bool bSuccess);
	void OnJoinSessionComplete(FName SessionName,
		EOnJoinSessionCompleteResult::Type Result);
	void OnNetworkFailure(UWorld* World, UNetDriver* NetDriver,
		ENetworkFailure::Type FailureType, const FString& ErrorString);

public:
	virtual void Init() override;


	virtual void Host(const FString& ServerName) override;
	virtual void Join(const int& Index,
		const FPServerData& InServerData) override;
	virtual void StartGame() override;
	virtual void LoadMainMenu() override;
	virtual void RefreshServerList() override;
};
