// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParentWidget.h"
#include "ActiveHUD.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class PP_API UActiveHUD : public UParentWidget
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAcces = true))
		UButton* m_CancelButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAcces = true))
		UButton* m_RefreshButton;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAcces = true))
		UButton* m_RefreshMenu;*/

protected:
	virtual bool Initialize() override;

	UFUNCTION() void RestartGame();
	UFUNCTION() void QuitGame();
};
