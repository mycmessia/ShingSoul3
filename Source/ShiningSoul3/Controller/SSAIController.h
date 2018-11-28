// Copyright Yuchen Mei and Matias Lavik. All rights reserved. :)

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "SSAIController.generated.h"

class UBehaviorTreeComponent;

/**
 * 
 */
UCLASS()
class SHININGSOUL3_API ASSAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	ASSAIController();

	virtual void Possess(APawn* Pawn) override;

	void SetSeenTarget(APawn* Pawn);

	UPROPERTY(EditDefaultsOnly, Category = "AI")
		FName BlackboardKeyTarget = "Target";

private:
	UBehaviorTreeComponent* BehaviourTreeComp;
	
	UBlackboardComponent* BlackboardComp;
};