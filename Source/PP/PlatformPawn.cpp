// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformPawn.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APlatformPawn::APlatformPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));;
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Comp"));
	StaticMeshComp->SetCollisionProfileName("PhysicsActor");

	RootComponent = BoxComp;
	StaticMeshComp->SetupAttachment(RootComponent);
	BoxComp->SetCollisionProfileName(FName("PhysicsActor"));
	BoxComp->SetBoxExtent(FVector(175.0f, 50.0f, 50.0f));

	bReplicates = true;

}

// Called when the game starts or when spawned
void APlatformPawn::BeginPlay()
{
	Super::BeginPlay();
	
	SetReplicateMovement(true);
}

// Called every frame
void APlatformPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
}

void APlatformPawn::Move_Implementation(float Value)
{
	CurrentVelocity.X = FMath::Clamp(Value, -1.0f, 1.0f) * 100.0f;

	if (CurrentVelocity.X < 0.0f && GetActorLocation().X < -320.f)
	{
		CurrentVelocity.X = 0.f;
		return;
	}

	if (CurrentVelocity.X > 0.0f && GetActorLocation().X > 220.f)
	{
		CurrentVelocity.X = 0.f;
		return;
	}
}

