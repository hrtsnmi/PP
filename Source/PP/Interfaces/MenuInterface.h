// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MenuInterface.generated.h"

struct FPServerData;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMenuInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PP_API IMenuInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Host(const FString& ServerName) = 0;
	virtual void Join(const int& Index, const FPServerData& InServerData) = 0;
	virtual void StartGame() = 0;
	virtual void LoadMainMenu() = 0;
	virtual void RefreshServerList() = 0;
};