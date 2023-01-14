#include "TT/Turtle/Public/TTTurtleSecondTask.h"
#include "TT/Meta/Public/TTPatrolPoint.h"


ATTTurtleSecondTask::ATTTurtleSecondTask()
{

}

void ATTTurtleSecondTask::BeginPlay()
{
	Super::BeginPlay();

	StopMoving();
}

void ATTTurtleSecondTask::MoveToDestination()
{
	MoveSpeed = 300.f;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATTTurtleSecondTask::StopMoving, 1.0f, true);
}

void ATTTurtleSecondTask::StopMoving()
{
	MoveSpeed = 0.f;
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATTTurtleSecondTask::MoveToDestination, 1.0f, true);
}
