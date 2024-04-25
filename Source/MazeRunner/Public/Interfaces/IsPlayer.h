// Copyright Siddharth Jaiswal

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IsPlayer.generated.h"

UINTERFACE()
class UIsPlayer : public UInterface
{
	GENERATED_BODY()
};

class MAZERUNNER_API IIsPlayer
{
	GENERATED_BODY()

public:
	virtual void PlayerDeath() = 0;
	virtual void EnemyDeath() = 0;

	virtual void AddCollectable_Coin() = 0;

	virtual void AddAbility_Flight(bool Begin) = 0;
	virtual void AddAbility_Hide(bool Begin) = 0;
};
