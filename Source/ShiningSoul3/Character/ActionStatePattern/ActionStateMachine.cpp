// Fill out your copyright notice in the Description page of Project Settings.

#include "ActionStateMachine.h"

FActionStateMachine::FActionStateMachine()
{
}

FActionStateMachine::~FActionStateMachine()
{
}

void FActionStateMachine::Update()
{
	if (CurrentState.IsValid())
	{
		CurrentState->Update();
	}
}

void FActionStateMachine::ChangeState(TUniquePtr<FActionState> NewState)
{
	if (CurrentState.IsValid())
	{
		CurrentState->End();
	}

	if (NewState.IsValid())
	{
		NewState->Start();
	}
}
