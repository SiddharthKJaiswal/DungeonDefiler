// Copyright Siddharth Jaiswal

#include "Pawns/MyCharacterNonPlayer.h"

#include "AIController.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "Pawns/MyCharacterPlayer.h"
#include "Perception/PawnSensingComponent.h"

AMyCharacterNonPlayer::AMyCharacterNonPlayer()
{
	GetCapsuleComponent()->SetCapsuleSize(35.0f, 90.0f);

	//GetMesh()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetCollisionObjectType(ECC_PhysicsBody);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	KillCollision = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	KillCollision->SetupAttachment(GetMesh(), "pelvis");
	KillCollision->SetBoxExtent(FVector(70.0f, 35.0f, 35.0f));
	KillCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
	KillCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	KillCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	PawnSensor = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensor");
	PawnSensor->HearingThreshold = 350.0f;
	PawnSensor->LOSHearingThreshold = 700.0f;
	PawnSensor->SightRadius = 1250.0f;
	PawnSensor->SetPeripheralVisionAngle(60.0f);
	PawnSensor->OnSeePawn.AddDynamic(this, &AMyCharacterNonPlayer::OnSeePlayerPawn);
}

void AMyCharacterNonPlayer::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	Reference_AIController = Cast<AAIController>(NewController);
	KillCollision->OnComponentBeginOverlap.AddDynamic(this, &AMyCharacterNonPlayer::OnHitKillBox);
}

void AMyCharacterNonPlayer::OnThisPawnDeath()
{
	Super::OnThisPawnDeath();

	PawnSensor->Deactivate();
	KillCollision->DestroyComponent();
	//Notify NPC Death
	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyCharacterNonPlayer::DestroyThis, 3.0f, false);
}

void AMyCharacterNonPlayer::DestroyThis()
{
	Destroy();
}

void AMyCharacterNonPlayer::OnSeePlayerPawn(APawn* InPawn)
{
	if (const AMyCharacterPlayer* PlayerPawn = Cast<AMyCharacterPlayer>(InPawn))
	{
		if (PlayerPawn->bIsPawnVisible)
		{
			Reference_AIController->MoveToLocation(PlayerPawn->GetNavAgentLocation(), 5.0f);
		}
	}
}

void AMyCharacterNonPlayer::OnHitKillBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (const AMyCharacterPlayer* PlayerPawn = Cast<AMyCharacterPlayer>(OtherActor))
	{
		if (PlayerPawn->bIsPawnVisible)
		{
			//Kill Player
			//Game Over
		}
	}
}
