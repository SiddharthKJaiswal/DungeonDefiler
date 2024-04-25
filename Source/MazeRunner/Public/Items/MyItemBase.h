// Copyright Siddharth Jaiswal

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyItemBase.generated.h"

#pragma region ForwardDeclarations
class USphereComponent;
#pragma endregion

UCLASS()
class MAZERUNNER_API AMyItemBase : public AActor
{
	GENERATED_BODY()

#pragma region Data

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "_My|Item|Component")
	TObjectPtr<USphereComponent> PawnCollider = nullptr;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "_My|Item|Component")
	TObjectPtr<UStaticMeshComponent> ItemMesh = nullptr;
#pragma endregion

#pragma region Functions

public:
	AMyItemBase();

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "_My|Item")
	void OnBeginOverlap_PawnCollider(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
#pragma endregion
};
