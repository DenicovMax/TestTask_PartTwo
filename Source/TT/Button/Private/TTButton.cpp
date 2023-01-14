#include "TT/Button/Public/TTButton.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "TT/Turtle/Public/TTTurtle.h"


ATTButton::ATTButton()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(Mesh);

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SphereCollision->SetupAttachment(Mesh);

	SpawnPoint = CreateDefaultSubobject<UBoxComponent>("SpawnPoint");
	SpawnPoint->SetupAttachment(Mesh);
}

void ATTButton::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	SetOwner(OtherActor);
}

void ATTButton::SpawnTurtle()
{
	const FTransform SpawnTransform(SpawnPoint->GetComponentRotation(), SpawnPoint->GetComponentLocation());

	const auto Turtle = GetWorld()->SpawnActorDeferred<ATTTurtle>(TurtleClass, SpawnPoint->GetComponentTransform(),
	                                                              this, nullptr,
	                                                              ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);

	Turtle->PatrolPoint = PatrolPoints;
	Turtle->FinishSpawning(SpawnTransform);
}
