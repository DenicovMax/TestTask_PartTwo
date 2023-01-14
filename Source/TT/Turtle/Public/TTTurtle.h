#pragma once

#include "CoreMinimal.h"
#include "TTTurtle.generated.h"

class UBoxComponent;
class ATTPatrolPoint;

UCLASS()
class TT_API ATTTurtle : public APawn
{
	GENERATED_BODY()

public:
	ATTTurtle();

	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Speed")
	float MoveSpeed = 300.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Speed")
	float MoveAcceleration = 1024.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Speed")
	float RotationSpeed = 100.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement|Speed")
	float RotationAcceleration = 1024.f;

public:
	UPROPERTY(EditAnywhere)
	TArray<ATTPatrolPoint*> PatrolPoint;

	int32 PointIndex = 0;
	FVector Destination;

	float CurrentMoveSpeed     = 0.f;
	float CurrentRotationSpeed = 0.f;

	float ChacedMoveDelta;
	FRotator TargetRotation;
	FRotator TargetTurretRotation;

public:
	virtual void PerfomMovement(float DeltaTime);
	void AddTurtleMovementInput(float MoveDelta);
	void AddTurtleRotationInput(FRotator RotationDelta);
};
