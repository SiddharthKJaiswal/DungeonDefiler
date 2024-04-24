// Copyright Siddharth Jaiswal

#pragma once

#include "CoreMinimal.h"
#include "Pawns/MyCharacterBase.h"
#include "MyCharacterNonPlayer.generated.h"

class UBoxComponent;
class AAIController;
class UPawnSensingComponent;

UCLASS()
class DUNGEONDEFILER_API AMyCharacterNonPlayer : public AMyCharacterBase
{
	GENERATED_BODY()

#pragma region Data

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "MyScript|Pawn|NPC|Components")
	TObjectPtr<UPawnSensingComponent> PawnSensor = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "MyScript|Pawn|NPC|Components")
	TObjectPtr<UBoxComponent> KillCollision = nullptr;

private:
	UPROPERTY()
	TObjectPtr<AAIController> Reference_AIController = nullptr;
#pragma endregion

#pragma region Functions

public:
	AMyCharacterNonPlayer();

	virtual void OnThisPawnDeath() override;

protected:
	virtual void PossessedBy(AController* NewController) override;

private:
	UFUNCTION()
	void OnSeePlayerPawn(APawn* InPawn);

	UFUNCTION()
	void OnHitKillBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void DestroyThis();
#pragma endregion
};
