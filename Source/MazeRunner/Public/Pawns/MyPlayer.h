// Copyright Siddharth Jaiswal

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/IsPlayer.h"
#include "MyPlayer.generated.h"

UCLASS()
class MAZERUNNER_API AMyPlayer : public ACharacter, public IIsPlayer
{
	GENERATED_BODY()

#pragma region Data

public:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "_My|Player")
	int32 Coins = 0;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "_My|Player")
	bool IsHiding = false;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "_My|Player")
	bool IsFlying = false;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "_My|Player")
    TObjectPtr<USkeletalMeshComponent> MeshArms = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "_My|Player")
	TObjectPtr<USkeletalMeshComponent> MeshGun = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "_My|Player")
	TObjectPtr<UMaterial> DefaultArmMat1 = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "_My|Player")
	TObjectPtr<UMaterial> DefaultArmMat2 = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "_My|Player")
	TObjectPtr<UMaterial> InvisibleArmMat = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "_My|Player")
	TObjectPtr<UMaterial> DefaultGunMat = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "_My|Player")
	TObjectPtr<UMaterial> InvisibleGunMat = nullptr;

private:
	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "_My|Player", meta = (AllowPrivateAccess = true))
	float HideTimeLeft = 5.0;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite, Category = "_My|Player", meta = (AllowPrivateAccess = true))
	float FlightTimeLeft = 5.0;
#pragma endregion

#pragma region Functions

public:
	AMyPlayer();
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable, Category = "_My|PC")
	virtual void KillPlayer() override;
	UFUNCTION(BlueprintCallable, Category = "_My|PC")
	virtual void AddCollectable_Coin() override;
	UFUNCTION(BlueprintCallable, Category = "_My|PC")
	virtual void AddAbility_Flight(bool Begin) override;
	UFUNCTION(BlueprintCallable, Category = "_My|PC")
	virtual void AddAbility_Hide(bool Begin) override;
#pragma endregion
};
