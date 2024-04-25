// Copyright Siddharth Jaiswal

#include "Items/MyItemBase.h"
#include "Components/SphereComponent.h"

AMyItemBase::AMyItemBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("USceneComponent"));

	PawnCollider = CreateDefaultSubobject<USphereComponent>("USphereComponent");
	PawnCollider->SetupAttachment(RootComponent);
	PawnCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	PawnCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	PawnCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	PawnCollider->OnComponentBeginOverlap.AddDynamic(this, &AMyItemBase::OnBeginOverlap_PawnCollider);

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("UStaticMeshComponent");
	ItemMesh->SetupAttachment(RootComponent);
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	ItemMesh->SetCollisionResponseToAllChannels(ECR_Block);
}

void AMyItemBase::OnBeginOverlap_PawnCollider_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}
