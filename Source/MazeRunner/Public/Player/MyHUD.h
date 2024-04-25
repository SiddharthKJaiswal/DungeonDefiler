// Copyright Siddharth Jaiswal

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

UCLASS()
class MAZERUNNER_API AMyHUD : public AHUD
{
	GENERATED_BODY()

#pragma region Functions

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "_My|UI")
	void UpdatePlayerData(int32 ValueToUpdate, float NewValue);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "_My|UI")
	void UpdatePlayerDeath();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "_My|UI")
	void UpdatePlayerWin();
#pragma endregion
};
