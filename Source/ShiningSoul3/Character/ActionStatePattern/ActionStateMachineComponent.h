// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "ActionStateMachine.h"
#include "Components/ActorComponent.h"

#include "ActionStateMachineComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHININGSOUL3_API UActionStateMachineComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UActionStateMachineComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FActionStateMachine& GetStateMachine() { return Machine; };

protected:
	virtual void BeginPlay() override;

	FActionStateMachine Machine;
};
