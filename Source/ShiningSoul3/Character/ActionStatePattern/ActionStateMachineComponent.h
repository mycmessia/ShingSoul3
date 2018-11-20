// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ActionStateMachine.h"
#include "ActionStates/ActionState.h"					// Have to include this to fix an UHT bug https://answers.unrealengine.com/questions/424938/enum-parameter-with-ufunction.html
#include "Components/ActorComponent.h"

#include "ActionStateMachineComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHININGSOUL3_API UActionStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UActionStateMachineComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FActionStateMachine& GetStateMachine() { return Machine; }

	UFUNCTION(BlueprintCallable)
	bool IsInState(EActionState StateEnum);

protected:
	virtual void BeginPlay() override;

	FActionStateMachine Machine;
};
