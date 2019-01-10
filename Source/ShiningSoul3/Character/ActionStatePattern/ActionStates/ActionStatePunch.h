// Copyright Yuchen Mei and Matias Lavik. All rights reserved. : )

#pragma once

#include "CoreMinimal.h"

#include "ActionState.h"

/**
 * 
 */
class SHININGSOUL3_API FActionStatePunch : public FActionState
{
public:
	FActionStatePunch();
	virtual ~FActionStatePunch();

	virtual void Enter();
	virtual void Update();
	virtual void Exit();
};
