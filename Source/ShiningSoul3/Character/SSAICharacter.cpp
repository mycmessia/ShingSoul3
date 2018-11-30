// Copyright Yuchen Mei and Matias Lavik. All rights reserved. :)

#include "SSAICharacter.h"

#include "BehaviorTree/BehaviorTree.h"
#include "Controller/SSAIController.h"
#include "Perception/PawnSensingComponent.h"


FName ASSAICharacter::PawnSensingCompName(TEXT("PawnSensingComp"));

// Sets default values
ASSAICharacter::ASSAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>(PawnSensingCompName);
	PawnSensingComp->SetPeripheralVisionAngle(90.0f);
}

// Called when the game starts or when spawned
void ASSAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &ASSAICharacter::OnSeePlayer);
	}
}

void ASSAICharacter::OnSeePlayer(APawn* Pawn)
{
	ASSAIController* AIController = Cast<ASSAIController>(GetController());
	//Set the seen target on the blackboard
	if (AIController)
	{
		AIController->SetSeenTarget(Pawn);
	}
}