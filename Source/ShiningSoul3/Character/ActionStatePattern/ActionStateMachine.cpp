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

void FActionStateMachine::ChangeState(EActionState NewStateEnum)
{
	if (CurrentStateEnum != NewStateEnum)
	{
		if (CurrentState.IsValid())
		{
			CurrentState->Exit();
		}

		TSharedPtr<FActionState> NewState = CreateState(NewStateEnum);

		if (NewState.IsValid())
		{
			NewState->Enter();
			CurrentState = NewState;
			CurrentStateEnum = NewStateEnum;
		}
	}
}

TSharedPtr<FActionState> FActionStateMachine::CreateState(EActionState NewState)
{
	switch (NewState)
	{
	case EActionState::Idle:
		return MakeShared<FActionStateIdle>();
	case EActionState::Punch:
		return MakeShared<FActionStatePunch>();
	default:
		break;
	}

	return nullptr;
}
