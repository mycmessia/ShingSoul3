// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ActionStates/ActionState.h"

/**
 * 
 */
class SHININGSOUL3_API FActionStateMachine
{
public:
	FActionStateMachine();
	~FActionStateMachine();

	TSharedPtr<FActionState> CurrentState;

	void Update();

	void ChangeState(TUniquePtr<FActionState> NewState);
};
