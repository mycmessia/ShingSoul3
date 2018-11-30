// Copyright Yuchen Mei and Matias Lavik. All rights reserved. :)

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SSAICharacter.generated.h"

UCLASS()
class SHININGSOUL3_API ASSAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASSAICharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "AI")
		class UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(EditAnywhere, Category = "AI")
		class UBehaviorTree* BehaviourTree;

	static FName PawnSensingCompName;

private:
	UFUNCTION()
		void OnSeePlayer(APawn* Pawn);
};
