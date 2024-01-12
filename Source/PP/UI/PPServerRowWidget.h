// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Headers/PPData.h"
#include "PPServerRowWidget.generated.h"

/**
 * 
 */
class UTextBlock;
class UButton;
class UMainMenu;

UCLASS()
class PP_API UPPServerRowWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Setup(UMainMenu* InParent, uint32 const InIndex);

	FPPServerDataStruct GetServerData() const { return ServerData; }
	UTextBlock* GetServerName() const { return ServerName; }
	UTextBlock* GetHostUser() const { return HostUser; }
	UTextBlock* GetConnectionFraction() const { return ConnectionFraction; }
	bool GetIsSelected() const { return bIsSelected; }

	void SetServerData(FPPServerDataStruct const& InServerData);
	void SetRowIsSelected(bool const InSelected);

protected:
	UFUNCTION()
		void OnRowClicked();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
		UTextBlock* ServerName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
		UTextBlock* HostUser;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
		UTextBlock* ConnectionFraction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAccess = true))
		UButton* RowButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
		UMainMenu* Parent;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
		bool bIsSelected{ false };

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
		FPPServerDataStruct ServerData;

	uint32 Index;
};
