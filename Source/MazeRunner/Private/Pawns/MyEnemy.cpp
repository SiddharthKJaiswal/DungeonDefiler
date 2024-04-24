// Copyright Siddharth Jaiswal

#include "Pawns/MyEnemy.h"
#include "AIController.h"
#include "Components/BoxComponent.h"
#include "Interfaces/IsPlayer.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Pawns/MyPlayer.h"
#include "Perception/PawnSensingComponent.h"

AMyEnemy::AMyEnemy()
{
	PrimaryActorTick.bCanEverTick = false;

	GetCapsuleComponent()->InitCapsuleSize(35.0f, 90.0f);

	GetMesh()->SetRelativeLocation(FVector(0.0f, 0.0f, -90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));

	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComponent");
	PawnSensingComponent->SensingInterval = 0.25f;
	PawnSensingComponent->SetPeripheralVisionAngle(60.0f);
	PawnSensingComponent->SightRadius = 1250.0f;
	PawnSensingComponent->HearingThreshold = 350.0f;
	PawnSensingComponent->LOSHearingThreshold = 700.0f;

	KillBox = CreateDefaultSubobject<UBoxComponent>("UBoxComponent");
	KillBox->SetupAttachment(GetMesh());
	KillBox->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
	KillBox->SetBoxExtent(FVector(50.0f, 50.0f, 70.0f));
	KillBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	KillBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void AMyEnemy::BeginPlay()
{
	Super::BeginPlay();

	KillBox->OnComponentBeginOverlap.AddDynamic(this, &AMyEnemy::OnBeginOverlap_KillBox);

	PawnSensingComponent->OnSeePawn.AddDynamic(this, &AMyEnemy::OnSeePawn_PawnSensingComponent);
	PawnSensingComponent->OnHearNoise.AddDynamic(this, &AMyEnemy::OnHearNoise_PawnSensingComponent);
}

void AMyEnemy::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	Reference_AIController = Cast<AAIController>(NewController);
}

void AMyEnemy::OnBeginOverlap_KillBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IIsPlayer* PlayerPawn = Cast<IIsPlayer>(OtherActor))
	{
		PlayerPawn->KillPlayer();
	}
}

void AMyEnemy::OnSeePawn_PawnSensingComponent(APawn* Pawn)
{
	if (Cast<AMyPlayer>(Pawn)->IsHiding)
	{
		Reference_AIController->StopMovement();
		return;
	}
	Reference_AIController->MoveToLocation(Pawn->GetNavAgentLocation());
}

void AMyEnemy::OnHearNoise_PawnSensingComponent(APawn* Pawn, const FVector& Location, float Volume)
{
}

void AMyEnemy::KillEnemy()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	KillBox->DestroyComponent();
	GetMovementComponent()->StopMovementImmediately();
	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	GetMesh()->SetSimulatePhysics(true);
	SetLifeSpan(3.0f);
}
