#pragma once

#include "CoreMinimal.h"
#include "TTTurtle.h"
#include "TTTurtleThirdTask.generated.h"

UCLASS()
class TT_API ATTTurtleThirdTask : public ATTTurtle
{
	GENERATED_BODY()

public:
	ATTTurtleThirdTask();

	void BeginPlay() override;

public:
	void MoveToDestination();
	void StopMoving();

public:
	FTimerHandle TimerHandle;
};
