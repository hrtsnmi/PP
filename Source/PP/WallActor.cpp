// Fill out your copyright notice in the Description page of Project Settings.


#include "WallActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AWallActor::AWallActor()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Comp"));
	StaticMeshComp->SetupAttachment(RootComponent);
	
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));
	BoxComp->SetupAttachment(StaticMeshComp);
	BoxComp->SetBoxExtent(FVector(100.0f, 2500.0f, 100.0f));
	BoxComp->SetCollisionProfileName(FName("PhysicsActor"));
	
	

}

// Called when the game starts or when spawned
void AWallActor::BeginPlay()
{
	Super::BeginPlay();
	
}

