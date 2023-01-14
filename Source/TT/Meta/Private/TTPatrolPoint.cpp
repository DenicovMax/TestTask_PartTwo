#include "TT/Meta/Public/TTPatrolPoint.h"

#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "Particles/ParticleSystemComponent.h"


ATTPatrolPoint::ATTPatrolPoint()
{
	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SetRootComponent(SphereCollision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Mesh->SetupAttachment(SphereCollision);

	FXComponent = CreateDefaultSubobject<UParticleSystemComponent>("FXComponent");
	FXComponent->SetupAttachment(SphereCollision);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>("AudioComponent");
	AudioComponent->SetupAttachment(SphereCollision);
}

void ATTPatrolPoint::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	FXComponent->ActivateSystem();
	AudioComponent->Activate();
}
