// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TTButton.generated.h"

class UBoxComponent;
class ATTPatrolPoint;
class ATTTurtle;
class USphereComponent;

UCLASS()
class TT_API ATTButton : public AActor
{
	GENERATED_BODY()

public:
	ATTButton();

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere)
	UBoxComponent* SpawnPoint;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATTTurtle> TurtleClass;

public:
	UPROPERTY(EditAnywhere)
	TArray<ATTPatrolPoint*> PatrolPoints;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void SpawnTurtle();
};
