// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ParentWidget.h"
#include "InGameMenu.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class PP_API UInGameMenu : public UParentWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAcces = true))
		UButton* m_ResumeButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAcces = true))
		UButton* m_LeaveSessionButton;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget, AllowPrivateAcces = true))
		UButton* m_QuitButton;

protected:
	virtual bool Initialize() override;

	UFUNCTION() void ResumePressed();
	UFUNCTION() void LeaveGamePressed();
	UFUNCTION() void QuitGamePressed();
};
