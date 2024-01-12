// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParentWidget.h"
#include "MainMenu.generated.h"

class UButton;
class UWidgetSwitcher;

struct FPPServerDataStruct;

DECLARE_LOG_CATEGORY_EXTERN(LogUnrealPongUI, Log, All);

UCLASS()
class PP_API UMainMenu : public UParentWidget
{
	GENERATED_BODY()
	
public:
	void SetActiveWidget(const int& Index);
	void SetServerList(TArray<FPPServerDataStruct> ServerNames);
	void SelectserverRowIndex(const uint32 Index);

protected:
	explicit UMainMenu(FObjectInitializer const& ObjectInitializer);
	virtual bool Initialize() override;

private:
	void UpdateServerRowChildren();

	//Funcs to UI elements
	UFUNCTION()
		void HostServer();

	UFUNCTION()
		void JoinServer();
	UFUNCTION()
		void QuitPressed();
	UFUNCTION()
		void OpenMainMenu();
	UFUNCTION()
		void OpenJoinMenu();
	UFUNCTION()
		void RefreshServerList();

	// UI elements binding
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
		UWidgetSwitcher* m_Switcher;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
		UWidget* m_MainMenu;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
		UWidget* m_JoinMenu;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
		UPanelWidget* m_ServerList;

	//buttons
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
		UButton* m_ButtonHost;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
		UButton* m_ButtonJoin;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
		UButton* m_ButtonQuit;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
		UButton* m_CancelJoinButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
		UButton* m_RefreshButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
		UButton* m_ConfirmButton;

	/** Class References */

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true),
		Category = "MainMenu|Config")
		TSubclassOf<UUserWidget> ServerRowWidgetClass;

	/** unexposed variables */

	TOptional<uint32> SelectedServerRowIndex;
};
