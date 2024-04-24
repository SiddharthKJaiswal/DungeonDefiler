// Copyright Siddharth Jaiswal

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IsEnemy.generated.h"

UINTERFACE()
class UIsEnemy : public UInterface
{
	GENERATED_BODY()
};

class MAZERUNNER_API IIsEnemy
{
	GENERATED_BODY()

public:
	virtual void KillEnemy() = 0;
};
