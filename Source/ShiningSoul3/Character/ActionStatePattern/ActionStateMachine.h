// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ActionStates/ActionStates.h"

/**
 * 
 */
class SHININGSOUL3_API FActionStateMachine
{
public:
	FActionStateMachine();
	~FActionStateMachine();

	TSharedPtr<FActionState> CurrentState;
	EActionState CurrentStateEnum;

	void Update();

	void ChangeState(EActionState NewStateEnum);

	TSharedPtr<FActionState> CreateState(EActionState NewState);
};
