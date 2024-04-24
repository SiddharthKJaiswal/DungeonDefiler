// Copyright Siddharth Jaiswal

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/IsEnemy.h"
#include "MyEnemy.generated.h"

class UBoxComponent;
class AAIController;
class UPawnSensingComponent;

UCLASS()
class MAZERUNNER_API AMyEnemy : public ACharacter, public IIsEnemy
{
	GENERATED_BODY()

#pragma region Data

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "_My|Enemy")
	TObjectPtr<AAIController> Reference_AIController = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "_My|Enemy")
	TObjectPtr<UBoxComponent> KillBox = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "_My|Enemy")
	TObjectPtr<UPawnSensingComponent> PawnSensingComponent = nullptr;

#pragma endregion

#pragma region Functions

public:
	AMyEnemy();

	UFUNCTION(BlueprintCallable, Category = "_My|NPC")
	virtual void KillEnemy() override;

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;

	UFUNCTION(BlueprintCallable, Category = "_My|NPC")
	void OnBeginOverlap_KillBox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION(BlueprintCallable, Category = "_My|NPC")
	void OnSeePawn_PawnSensingComponent(APawn* Pawn);

	UFUNCTION(BlueprintCallable, Category = "_My|NPC")
	void OnHearNoise_PawnSensingComponent(APawn* Pawn, const FVector& Location, float Volume);
#pragma endregion
};
