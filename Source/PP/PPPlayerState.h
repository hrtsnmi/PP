// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PPPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PP_API APPPlayerState : public APlayerState
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(Replicated)
	bool bPlayAgain{false};

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

public:
	bool GetPlayAgain() const { return bPlayAgain; }

	UFUNCTION(Server, Reliable)
		void  SetPlayAgain(bool bInPlayAgain);
};
