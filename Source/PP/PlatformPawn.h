// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/PlatformMovementInterface.h"
#include "PlatformPawn.generated.h"



UCLASS()
class PP_API APlatformPawn :
	public APawn, public IPlatformMovementInterface
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* BoxComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* StaticMeshComp;

	FVector CurrentVelocity{};

public:
	// Sets default values for this pawn's properties
	APlatformPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Move_Implementation(float Value);

	UStaticMeshComponent* GetStaticMesh() { return StaticMeshComp; }
};
