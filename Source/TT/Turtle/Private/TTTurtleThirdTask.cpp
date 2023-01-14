#include "TT/Turtle/Public/TTTurtleThirdTask.h"


ATTTurtleThirdTask::ATTTurtleThirdTask()
{

}

void ATTTurtleThirdTask::BeginPlay()
{
	Super::BeginPlay();

	MoveToDestination();
}

void ATTTurtleThirdTask::MoveToDestination()
{
	MoveSpeed = 300.f;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATTTurtleThirdTask::StopMoving, 1.0f, true);
}

void ATTTurtleThirdTask::StopMoving()
{
	MoveSpeed = -300.f;
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATTTurtleThirdTask::MoveToDestination, 0.5f, true);
}
