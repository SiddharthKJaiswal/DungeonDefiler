// Copyright Siddharth Jaiswal

#include "Pawns/MyPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(35.0f, 90.0f);
}

void AMyPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsFlying)
	{
		FlightTimeLeft -= DeltaSeconds;
		AddMovementInput(FVector(0.0f, 0.0f, 1.0f));
		if (FlightTimeLeft <= 0)
		{
			AddAbility_Flight(false);
		}
	}
	if (IsHiding)
	{
		HideTimeLeft -= DeltaSeconds;
		if (HideTimeLeft <= 0)
		{
			AddAbility_Hide(false);
		}
	}
}

void AMyPlayer::KillPlayer()
{
	if (IsHiding || IsFlying)
	{
		return;
	}
	UKismetSystemLibrary::PrintString(GetWorld(), "Begun Overlap With Player Pawn");
}

void AMyPlayer::AddCollectable_Coin()
{
	Coins++;
}

void AMyPlayer::AddAbility_Flight(const bool Begin)
{
	if (Begin)
	{
		IsFlying = true;
		FlightTimeLeft = 5.0f;
		GetCharacterMovement()->GravityScale = -1.0f;
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
	}
	else
	{
		IsFlying = false;
		FlightTimeLeft = 0.0f;
		GetCharacterMovement()->GravityScale = 1.0f;
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
	}
}

void AMyPlayer::AddAbility_Hide(const bool Begin)
{
	if (Begin)
	{
		IsHiding = true;
		HideTimeLeft = 5.0f;

		MeshArms->SetMaterial(0, InvisibleArmMat);
		MeshArms->SetMaterial(1, InvisibleArmMat);

		MeshGun->SetMaterial(0, InvisibleGunMat);
	}
	else
	{
		IsHiding = false;
		HideTimeLeft = 0.0f;
		MeshArms->SetMaterial(0, DefaultArmMat1);
		MeshArms->SetMaterial(1, DefaultArmMat2);

		MeshGun->SetMaterial(0, DefaultGunMat);
	}
}
