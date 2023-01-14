// Copyright Epic Games, Inc. All Rights Reserved.

#include "TT/Character/Public/TTCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "TT/Button/Public/TTButton.h"


ATTCharacter::ATTCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	BaseTurnRate   = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw   = false;
	bUseControllerRotationRoll  = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate              = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity             = 600.f;
	GetCharacterMovement()->AirControl                = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength         = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

}

void ATTCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("SpawnTurtle", IE_Pressed, this, &ATTCharacter::Activate);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATTCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATTCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATTCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATTCharacter::LookUpAtRate);

	PlayerInputComponent->BindTouch(IE_Pressed, this, &ATTCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ATTCharacter::TouchStopped);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ATTCharacter::OnResetVR);
}

void ATTCharacter::Activate()
{
	TArray<AActor*> OverlappingActors;
	GetCapsuleComponent()->GetOverlappingActors(OverlappingActors);
	for(AActor* Actor : OverlappingActors)
	{
		if(Actor->IsA(ATTButton::StaticClass()))
		{
			ATTButton* Item = Cast<ATTButton>(Actor);
			Item->SpawnTurtle();
			break;
		}
	}
}

void ATTCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ATTCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
	Jump();
}

void ATTCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
	StopJumping();
}

void ATTCharacter::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATTCharacter::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATTCharacter::MoveForward(float Value)
{
	if((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void ATTCharacter::MoveRight(float Value)
{
	if((Controller != nullptr) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}
