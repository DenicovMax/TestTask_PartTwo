// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TTCharacter.generated.h"

UCLASS(config=Game)
class ATTCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

public:
	ATTCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

protected:
	void OnResetVR();

	void MoveForward(float Value);
	void MoveRight(float Value);

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Activate();
	// End of APawn interface

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const
	{
		return CameraBoom;
	}

	FORCEINLINE class UCameraComponent* GetFollowCamera() const
	{
		return FollowCamera;
	}
};
