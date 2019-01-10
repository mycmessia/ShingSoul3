// Copyright Yuchen Mei and Matias Lavik. All rights reserved. : )

#pragma once

#include "CoreMinimal.h"
#include "ActionState.h"

/**
 * 
 */
class SHININGSOUL3_API FActionStateIdle : public FActionState
{
public:
	FActionStateIdle();
	virtual ~FActionStateIdle();

	virtual void Enter();
	virtual void Update();
	virtual void Exit();
};
