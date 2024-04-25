// Copyright Siddharth Jaiswal

#include "Pawns/MyPlayer.h"
#include "Player/MyHUD.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AMyPlayer::AMyPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(35.0f, 90.0f);
}

void AMyPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	Reference_HUD = Cast<AMyHUD>(Cast<APlayerController>(GetController())->GetHUD());
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
		if (Reference_HUD)
		{
			Reference_HUD->UpdatePlayerData(2, FlightTimeLeft);
		}
	}
	if (IsHiding)
	{
		HideTimeLeft -= DeltaSeconds;
		if (HideTimeLeft <= 0)
		{
			AddAbility_Hide(false);
		}
		if (Reference_HUD)
		{
			Reference_HUD->UpdatePlayerData(3, HideTimeLeft);
		}
	}
}

void AMyPlayer::PlayerDeath()
{
	if (IsHiding || IsFlying)
	{
		return;
	}
	Reference_HUD->UpdatePlayerDeath();
}

void AMyPlayer::EnemyDeath()
{
	EnemiesKilled++;
	Reference_HUD->UpdatePlayerData(1, static_cast<float>(EnemiesKilled));
}

void AMyPlayer::AddCollectable_Coin()
{
	Coins++;
	Reference_HUD->UpdatePlayerData(0, static_cast<float>(Coins));
}

void AMyPlayer::AddAbility_Flight(const bool Begin)
{
	if (Begin)
	{
		IsFlying = true;
		FlightTimeLeft = 5.0f;
		GetCharacterMovement()->GravityScale = -1.0f;
		GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		Reference_HUD->UpdatePlayerData(2, FlightTimeLeft);
	}
	else
	{
		IsFlying = false;
		FlightTimeLeft = 0.0f;
		GetCharacterMovement()->GravityScale = 1.0f;
		GetCharacterMovement()->SetMovementMode(MOVE_Walking);
		Reference_HUD->UpdatePlayerData(2, FlightTimeLeft);
	}
}

void AMyPlayer::AddAbility_Hide(const bool Begin)
{
	if (Begin)
	{
		IsHiding = true;
		HideTimeLeft = 5.0f;
		Reference_HUD->UpdatePlayerData(3, HideTimeLeft);
		//Set Mesh To Invisible
	}
	else
	{
		IsHiding = false;
		HideTimeLeft = 0.0f;
		Reference_HUD->UpdatePlayerData(3, HideTimeLeft);
		//Set Mesh To Visible
	}
}
