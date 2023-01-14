#pragma once

#include "CoreMinimal.h"
#include "TTTurtle.h"
#include "TTTurtleSecondTask.generated.h"

UCLASS()
class TT_API ATTTurtleSecondTask : public ATTTurtle
{
	GENERATED_BODY()

public:
	ATTTurtleSecondTask();

	void BeginPlay() override;

public:
	void MoveToDestination();
	void StopMoving();

public:
	FTimerHandle TimerHandle;

};
