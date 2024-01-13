// Fill out your copyright notice in the Description page of Project Settings.


#include "GateActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "BallActor.h"
#include "Kismet/GameplayStatics.h"
#include "PPGameState.h"

// Sets default values
AGateActor::AGateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Comp"));
	StaticMeshComp->SetupAttachment(RootComponent);

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));
	BoxComp->SetupAttachment(StaticMeshComp);
	BoxComp->SetBoxExtent(FVector(100.0f, 2500.0f, 100.0f));
	BoxComp->SetCollisionProfileName(FName("Trigger"));
}

// Called when the game starts or when spawned
void AGateActor::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &AGateActor::Score);
}

void AGateActor::Score(AActor* OverlappedActor, AActor* OtherActor)
{
	ABallActor* Ball = Cast<ABallActor>(OtherActor);
	if(Ball)
	{
		AGameStateBase* GameState = UGameplayStatics::GetGameState(this);
		if (GameState)
		{
			APPGameState* PPGameState = Cast<APPGameState>(GameState);
			if(PPGameState)
			{
				PPGameState->IncrementScoreAtPlayerID(PlayerNumber);
			}
		}
	}
}