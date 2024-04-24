// Copyright Siddharth Jaiswal

#pragma once

#include "CoreMinimal.h"
#include "Pawns/MyCharacterBase.h"
#include "MyCharacterPlayer.generated.h"

class UCameraComponent;

UCLASS()
class DUNGEONDEFILER_API AMyCharacterPlayer : public AMyCharacterBase
{
	GENERATED_BODY()

#pragma region Data

public:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "MyScripts|Pawn")
	bool bIsPawnVisible = true;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "MyScripts|Pawn")
	bool bIsPawnFlying = false;

protected:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "MyScripts|Pawn")
	float InvisibilityTimeLeft = 5.0f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "MyScripts|Pawn")
	float InvulnerabilityTimeLeft = 5.0f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "MyScript|Pawn|NPC|Components")
	TObjectPtr<UCameraComponent> FPCamera = nullptr;
#pragma endregion

#pragma region Functions

public:
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "MyScripts|Pawn")
	void Ability_Invisibility(bool StartAbility);

	UFUNCTION(BlueprintCallable, Category = "MyScripts|Pawn")
	void Ability_Invulnerability(bool StartAbility);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHitCapsule(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
#pragma endregion
};
