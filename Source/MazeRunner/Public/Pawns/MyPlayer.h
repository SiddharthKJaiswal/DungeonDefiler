// Copyright Siddharth Jaiswal

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/IsPlayer.h"
#include "MyPlayer.generated.h"

#pragma region ForwardDeclarations
class AMyHUD;
#pragma endregion

UCLASS()
class MAZERUNNER_API AMyPlayer : public ACharacter, public IIsPlayer
{
	GENERATED_BODY()

#pragma region Data

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "_My|Player|References", meta = (AllowPrivateAccess = true))
	TObjectPtr<AMyHUD> Reference_HUD = nullptr;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "_My|Player|Data", meta = (AllowPrivateAccess = true))
	int32 Coins = 0;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "_My|Player|Data", meta = (AllowPrivateAccess = true))
	int32 EnemiesKilled = 0;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "_My|Player|Data", meta = (AllowPrivateAccess = true))
	float HideTimeLeft = 0.0f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "_My|Player|Data", meta = (AllowPrivateAccess = true))
	float FlightTimeLeft = 0.0f;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "_My|Player|Data", meta = (AllowPrivateAccess = true))
	bool IsHiding = false;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "_My|Player|Data", meta = (AllowPrivateAccess = true))
	bool IsFlying = false;
#pragma endregion

#pragma region Functions

public:
	AMyPlayer();
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "_My|PC")
	virtual void PlayerDeath() override;
	UFUNCTION(BlueprintCallable, Category = "_My|PC")
	virtual void EnemyDeath() override;
	UFUNCTION(BlueprintCallable, Category = "_My|PC")
	virtual void AddCollectable_Coin() override;
	UFUNCTION(BlueprintCallable, Category = "_My|PC")
	virtual void AddAbility_Flight(bool Begin) override;
	UFUNCTION(BlueprintCallable, Category = "_My|PC")
	virtual void AddAbility_Hide(bool Begin) override;

	FORCEINLINE int32 Get_Coins() const { return Coins; }
	FORCEINLINE int32 Get_EnemiesKilled() const { return EnemiesKilled; }
	FORCEINLINE float Get_HideTimeLeft() const { return HideTimeLeft; }
	FORCEINLINE float Get_FlightTimeLeft() const { return FlightTimeLeft; }
	FORCEINLINE bool Get_IsHiding() const { return IsHiding; }
	FORCEINLINE bool Get_IsFlying() const { return IsFlying; }

protected:
	virtual void PossessedBy(AController* NewController) override;
#pragma endregion
};
