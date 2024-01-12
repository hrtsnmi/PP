// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/MenuInterface.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Headers\PPData.h"
#include "UI\MainMenu.h"
#include "UI\InGameMenu.h"
#include "UI\ActiveHUD.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instance|Config")
		FPPServerDataStruct ServerData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instance|Config")
		class UMainMenu* MainMenu;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instance|Config")
		class UActiveHUD* GameHUD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Instance|Config")
		class UInGameMenu* InGameMenu;

	/// Blueprint References, to be set in Editor on defaults

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance|Config")
		TSubclassOf<UUserWidget> MainMenuClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance|Config")
		TSubclassOf<UUserWidget> GameHUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Instance|Config")
		TSubclassOf<UUserWidget> InGameMenuClass;
	
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
		const FPPServerDataStruct& InServerData) override;
	virtual void StartGame() override;
	virtual void LoadMainMenu() override;
	virtual void RefreshServerList() override;

	/// UI Creation

	UFUNCTION(BlueprintCallable, Category = "Instance|UI")
		void LoadMainMenuWidget();

	UFUNCTION(BlueprintCallable, Category = "Instance|UI")
		void LoadActiveHUDWidget();

	UFUNCTION(BlueprintCallable, Category = "Instance|UI")
		void LoadInGameMenuWidget();

	/// UI Getters

	UActiveHUD* GetGameHUD() const { return GameHUD; }
};
