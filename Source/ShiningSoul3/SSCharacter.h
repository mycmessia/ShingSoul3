// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Character/ActionStatePattern/ActionStates/ActionStates.h"
#include "Character/ActionStatePattern/ActionStateMachine.h"
#include "Character/ActionStatePattern/ActionStateMachineComponent.h"
#include "BaseCharacter.h"

#include "SSCharacter.generated.h"

/**
 * 
 */
UCLASS(config=Game)
class SHININGSOUL3_API ASSCharacter : public ABaseCharacter
{
	GENERATED_BODY()
public:
    ASSCharacter();

    /** Returns CameraBoom subobject **/
    FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoomComp; }

    /** Returns FollowCamera subobject **/
    FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCameraComp; }

    /** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Camera)
        float BaseTurnRate;

    /** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
    UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=Camera)
        float BaseLookUpRate;
	
protected:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	virtual void Punch();

	virtual void StopPunching();

private:
    /** Camera boom positioning the camera behind the character */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
        class USpringArmComponent* CameraBoomComp;

    /** Follow camera */
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
        class UCameraComponent* FollowCameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = ActionState, meta = (AllowPrivateAccess = "true"))
		class UActionStateMachineComponent* ActionStateMachineComp;
};
