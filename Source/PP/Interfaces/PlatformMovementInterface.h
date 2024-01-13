// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlatformMovementInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlatformMovementInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class PP_API IPlatformMovementInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent) void Move(float Value);
};
