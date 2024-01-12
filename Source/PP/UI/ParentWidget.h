// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ParentWidget.generated.h"

/**
 * 
 */
class IMenuInterface;
UCLASS()
class PP_API UParentWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void Setup();
	void Teardown();

	IMenuInterface* GetMenuInterface() const { return MenuInterface; }
	void SetMenuInterface(IMenuInterface* InIMenuInterface);

protected:
	IMenuInterface* MenuInterface;
};
