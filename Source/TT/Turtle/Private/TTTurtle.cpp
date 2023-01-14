#include "TT/Turtle/Public/TTTurtle.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "TT/Button/Public/TTButton.h"
#include "TT/Meta/Public/TTPatrolPoint.h"


ATTTurtle::ATTTurtle()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	BoxCollision->SetupAttachment(Mesh);
}

void ATTTurtle::BeginPlay()
{
	Super::BeginPlay();

	if(ATTButton* Spawner = Cast<ATTButton>(GetInstigator()))
	{
		Spawner->PatrolPoints[PointIndex] = PatrolPoint[PointIndex];
	}
}

void ATTTurtle::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const FVector CurrentLocation = GetActorLocation();
	const FVector ForwardVector   = GetActorForwardVector();

	const FVector MovePosition = CurrentLocation + ForwardVector * MoveSpeed * DeltaSeconds;
	SetActorLocation(MovePosition, true);
	PerfomMovement(DeltaSeconds);

	AddTurtleMovementInput(1.f);
	AddTurtleRotationInput(PatrolPoint[PointIndex]->GetActorRotation());
}

void ATTTurtle::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	Destroy();
}

void ATTTurtle::PerfomMovement(float DeltaTime)
{
	if(FMath::IsNearlyZero(ChacedMoveDelta))
	{
		CurrentMoveSpeed = 0.f;
	}
	else
	{
		CurrentMoveSpeed = FMath::FInterpConstantTo(CurrentMoveSpeed, MoveSpeed * FMath::Abs(ChacedMoveDelta),
		                                            DeltaTime, MoveAcceleration);

		const FVector moveDelta = GetActorForwardVector() * CurrentMoveSpeed * DeltaTime * FMath::Sign(ChacedMoveDelta);
		SetActorLocation(GetActorLocation() + moveDelta);
	}

	ChacedMoveDelta = 0.f;

	if(TargetRotation == GetActorRotation())
	{
		CurrentRotationSpeed = 0.f;
	}
	else
	{
		CurrentRotationSpeed = FMath::FInterpConstantTo(CurrentRotationSpeed, RotationSpeed, DeltaTime,
		                                                RotationAcceleration);
		FRotator newRotation = FMath::RInterpConstantTo(GetActorRotation(), TargetRotation, DeltaTime,
		                                                CurrentRotationSpeed);
		newRotation.Roll  = GetActorRotation().Roll;
		newRotation.Pitch = GetActorRotation().Pitch;
		SetActorRotation(newRotation);
	}
}

void ATTTurtle::AddTurtleMovementInput(float MoveDelta)
{
	ChacedMoveDelta = MoveDelta;
}

void ATTTurtle::AddTurtleRotationInput(FRotator RotationDelta)
{
	TargetRotation = RotationDelta;
}
