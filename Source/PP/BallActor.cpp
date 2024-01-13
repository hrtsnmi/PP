// Fill out your copyright notice in the Description page of Project Settings.


#include "BallActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlatformPawn.h"
#include "WallActor.h"
#include "GateActor.h"

// Sets default values
ABallActor::ABallActor()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh Comp"));
	RootComponent = StaticMeshComp;
	StaticMeshComp->SetSimulatePhysics(true);
	StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMeshComp->SetEnableGravity(false);
	StaticMeshComp->SetConstraintMode(EDOFMode::XYPlane);

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Comp"));;
	BoxComp->SetupAttachment(StaticMeshComp);
	BoxComp->SetCollisionProfileName("Trigger");
	BoxComp->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));

	bGameOver = false;

	//BallMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Ball Movement Component"));
	//BallMovementComponent->InitialSpeed = 300.f;
	//BallMovementComponent->ProjectileGravityScale = 0;
}

// Called when the game starts or when spawned
void ABallActor::BeginPlay()
{
	Super::BeginPlay();
	
	SetReplicateMovement(true);
	
	if(BallMesh)
	{
		StaticMeshComp->SetStaticMesh(BallMesh);
	}

	OnActorBeginOverlap.AddDynamic(this, &ABallActor::OnPlatformHit);
}

// Called every frame
void ABallActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);
}

void ABallActor::Start()
{
	bGameOver = false;

	Restart();
}

void ABallActor::Restart_Implementation()
{
	SetActorLocation(FVector::ZeroVector);
	/*StaticMeshComp->SetPhysicsLinearVelocity(
		FVector(FMath::RandRange(-1000.f, 1000.f),
			(FMath::RandBool() ? 1.f : -1.f) * 500.f,
			0.f));*/

	CurrentVelocity = FVector(FMath::RandRange(-500.f, 500.f),
		(FMath::RandBool() ? 1.f : -1.f) * 500.f,
		0.f);
}

void ABallActor::GameOver()
{
	bGameOver = true;
	StaticMeshComp->SetPhysicsLinearVelocity(FVector::ZeroVector);
}

//void ABallActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
//{
//	if (!OtherActor || OtherActor == this)
//	{
//		return;
//	}
//
//}

void ABallActor::Move_Implementation(float DeltaTime)
{
	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
}

void ABallActor::OnPlatformHit(AActor* OverlappedActor, AActor* OtherActor)
{
	APlatformPawn* PlatformPawn = Cast<APlatformPawn>(OtherActor);
	if (PlatformPawn && PlatformPawn->IsValidLowLevel())
	{
		/*const FVector BallLinearVelocity = StaticMeshComp->GetPhysicsLinearVelocity();
		const FVector PlatformLinearVelocity = PlatformPawn->GetStaticMesh()->GetPhysicsLinearVelocity();
		const FVector NewBallLinearVelocity =
			FVector(PlatformLinearVelocity.X + FMath::RandRange(-1000.f, 1000.f),
				BallLinearVelocity.Y * -1.f, BallLinearVelocity.Z);

		StaticMeshComp->SetPhysicsLinearVelocity(NewBallLinearVelocity);*/

		const FVector BallLinearVelocity = CurrentVelocity;
		const FVector PlatformLinearVelocity = PlatformPawn->GetStaticMesh()->GetPhysicsLinearVelocity();
		const FVector NewBallLinearVelocity =
			FVector(PlatformLinearVelocity.X + FMath::RandRange(-1000.f, 1000.f),
				BallLinearVelocity.Y * -1.f, BallLinearVelocity.Z);


		CurrentVelocity = NewBallLinearVelocity;
	}

	AWallActor* Wall = Cast<AWallActor>(OtherActor);
	if (Wall && Wall->IsValidLowLevel())
	{
		/*const FVector BallLinearVelocity = StaticMeshComp->GetPhysicsLinearVelocity();
		const FVector NewBallLinearVelocity =
			FVector(BallLinearVelocity.X * -1.f, BallLinearVelocity.Y, BallLinearVelocity.Z);

		StaticMeshComp->SetPhysicsLinearVelocity(NewBallLinearVelocity);*/

		const FVector BallLinearVelocity = CurrentVelocity;
		const FVector NewBallLinearVelocity =
			FVector(BallLinearVelocity.X * -1.f, BallLinearVelocity.Y, BallLinearVelocity.Z);

		CurrentVelocity = NewBallLinearVelocity;
	}

	AGateActor* GateActor = Cast<AGateActor>(OtherActor);
	if (GateActor && GateActor->IsValidLowLevel())
	{
		Restart();
	}
}
