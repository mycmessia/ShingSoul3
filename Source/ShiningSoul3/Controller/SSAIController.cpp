// Copyright Yuchen Mei and Matias Lavik. All rights reserved. :)

#include "SSAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Character/SSAICharacter.h"

FName ASSAIController::BlackboardKeyTargetName(TEXT("Target"));
FName ASSAIController::BehaviourTreeCompName(TEXT("BehaviourTreeComp"));
FName ASSAIController::BlackboardCompName(TEXT("BlackboardComp"));

ASSAIController::ASSAIController()
{
	// Not a good example cause FName constructor is expensive. Will optimize it later.
	BehaviourTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(BehaviourTreeCompName);
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(BlackboardCompName);
}

void ASSAIController::Possess(APawn* Pawn)
{
	Super::Possess(Pawn);

	if (ASSAICharacter* AICharacter = Cast<ASSAICharacter>(Pawn))
	{
		if (UBehaviorTree* BT = AICharacter->BehaviourTree)
		{
			if (UBlackboardData* BlackboardData = BT->BlackboardAsset)
			{
				BlackboardComp->InitializeBlackboard(*BlackboardData);
				BehaviourTreeComp->StartTree(*BT);
			}
		}
	}
}

void ASSAIController::SetSeenTarget(APawn* Pawn)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValueAsObject(BlackboardKeyTargetName, Pawn);
	}
}
