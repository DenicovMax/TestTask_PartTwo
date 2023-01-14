// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TTPatrolPoint.generated.h"

class USphereComponent;
UCLASS()
class TT_API ATTPatrolPoint : public AActor
{
	GENERATED_BODY()

public:
	ATTPatrolPoint();

private:
	UPROPERTY(EditAnywhere)
	USphereComponent* SphereCollision;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* FXComponent;

	UPROPERTY(EditAnywhere)
	UAudioComponent* AudioComponent;

public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
