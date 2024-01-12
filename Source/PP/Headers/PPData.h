#pragma once

#include "PPData.generated.h"

USTRUCT(BlueprintType)
struct FPPServerDataStruct
{
	GENERATED_BODY()

public:
	UPROPERTY()
		FString Name;

	UPROPERTY()
		FString HostUsername;

	UPROPERTY()
		int PlayersAmount;
};