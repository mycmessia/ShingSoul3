// Copyright Yuchen Mei and Matias Lavik. All rights reserved. : )

#pragma once

#include "CoreMinimal.h"

UENUM()
enum class EActionState : uint8
{
	IDLE,
	PUNCH
};

/**
 * 
 */
class SHININGSOUL3_API FActionState
{
public:
	FActionState();
	virtual ~FActionState();

	virtual void Start();
	virtual void Update();
	virtual void End();
};