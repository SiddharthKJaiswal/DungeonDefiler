// Copyright Siddharth Jaiswal

#include "Pawns/MyCharacterPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void AMyCharacterPlayer::BeginPlay()
{
	Super::BeginPlay();

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacterPlayer::OnHitCapsule);

	FPCamera = CreateDefaultSubobject<UCameraComponent>("UCameraComponent");
	FPCamera->bUsePawnControlRotation = false;
	FPCamera->SetupAttachment(GetCapsuleComponent());
	FPCamera->SetRelativeLocation(FVector(10.0f, 0.0f, 60.0f));

	GetMesh()->SetupAttachment(FPCamera);
	GetMesh()->SetRelativeLocation(FVector(-10.0f, 0.0f, -150.0f));
}

void AMyCharacterPlayer::OnHitCapsule(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AActor* Collectable_Coin = Cast<AActor>(OtherActor))
	{
		//Notify Coin Collection
	}
	else if (AActor* Power_Invisibility = Cast<AActor>(OtherActor))
	{
		//Notify Invisibility Usage
		Ability_Invisibility(true);
	}
	else if (AActor* Power_Invulnerability = Cast<AActor>(OtherActor))
	{
		//Notify Invulnerability Usage
		Ability_Invulnerability(true);
	}
	OtherActor->Destroy();
}

void AMyCharacterPlayer::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!bIsPawnVisible)
	{
		if (InvisibilityTimeLeft <= 0.0f)
		{
			Ability_Invisibility(false);
		}
		else
		{
			InvisibilityTimeLeft -= DeltaSeconds;
		}
	}

	if (bIsPawnFlying)
	{
		if (InvulnerabilityTimeLeft <= 0.0f)
		{
			Ability_Invulnerability(false);
		}
		else
		{
			InvulnerabilityTimeLeft -= DeltaSeconds;
		}
	}
}

void AMyCharacterPlayer::Ability_Invisibility(const bool StartAbility)
{
	if (StartAbility)
	{
		bIsPawnVisible = false;
		InvisibilityTimeLeft = 5.0f;
		//Notify Power Up Usage
	}
	else
	{
		bIsPawnVisible = true;
		InvisibilityTimeLeft = 0.0f;
	}
}

void AMyCharacterPlayer::Ability_Invulnerability(const bool StartAbility)
{
	if (StartAbility)
	{
		bIsPawnFlying = true;
		InvulnerabilityTimeLeft = 5.0f;
		GetCharacterMovement()->GravityScale = -1.0f;
		//Notify Power Up Usage
	}
	else
	{
		bIsPawnFlying = false;
		InvulnerabilityTimeLeft = 0.0f;
		GetCharacterMovement()->GravityScale = 1.0f;
	}
}
