// Fill out your copyright notice in the Description page of Project Settings.

#include "SSCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"


ASSCharacter::ASSCharacter()
{
    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(42.f,96.0f);

    // set our turn rates for input
    BaseTurnRate = 45.f;
    BaseLookUpRate = 45.f;

    // Don't rotate when the controller rotates. Let that just affect the camera.
    bUseControllerRotationPitch = false;
    bUseControllerRotationYaw = false;
    bUseControllerRotationRoll = false;

    // Configure character movement
    GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
    GetCharacterMovement()->RotationRate = FRotator(0.0f,540.0f,0.0f); // ...at this rotation rate
    GetCharacterMovement()->JumpZVelocity = 600.f;
    GetCharacterMovement()->AirControl = 0.2f;

    // Create a camera boom (pulls in towards the player if there is a collision)
    CameraBoomComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoomComp"));
	CameraBoomComp->SetupAttachment(RootComponent);
	CameraBoomComp->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoomComp->bUsePawnControlRotation = true; // Rotate the arm based on the controller

    FollowCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCameraComp"));
	FollowCameraComp->SetupAttachment(CameraBoomComp,USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCameraComp->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	ActionStateMachineComp = CreateDefaultSubobject<UActionStateMachineComponent>(TEXT("ActionStateMachineComp"));

    // Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
    // are set in the derived blueprint asset named BP_SSCharacter (to avoid direct content references in C++)
}

void ASSCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    check(PlayerInputComponent);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

    PlayerInputComponent->BindAction("Punch", IE_Pressed, this, &ASSCharacter::Punch);
    PlayerInputComponent->BindAction("Punch", IE_Released, this, &ASSCharacter::StopPunching);

    PlayerInputComponent->BindAxis("MoveForward", this, &ASSCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASSCharacter::MoveRight);

    // We have 2 versions of the rotation bindings to handle different kinds of devices differently
    // "turn" handles devices that provide an absolute delta, such as a mouse.
    // "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("TurnRate", this, &ASSCharacter::TurnAtRate);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("LookUpRate", this, &ASSCharacter::LookUpAtRate);

    // handle touch devices
    PlayerInputComponent->BindTouch(IE_Pressed, this, &ASSCharacter::TouchStarted);
    PlayerInputComponent->BindTouch(IE_Released, this, &ASSCharacter::TouchStopped);
}

void ASSCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
    Jump();
}

void ASSCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
    StopJumping();
}

void ASSCharacter::Punch()
{
	ActionStateMachineComp->GetStateMachine().ChangeState(MakeUnique<FActionStatePunch>());
}

void ASSCharacter::StopPunching()
{
	ActionStateMachineComp->GetStateMachine().ChangeState(MakeUnique<FActionStateIdle>());
}

void ASSCharacter::TurnAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ASSCharacter::LookUpAtRate(float Rate)
{
    // calculate delta for this frame from the rate information
    AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ASSCharacter::MoveForward(float Value)
{
    if((Controller != NULL) && (Value != 0.0f))
    {
        // find out which way is forward
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get forward vector
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void ASSCharacter::MoveRight(float Value)
{
    if((Controller != NULL) && (Value != 0.0f))
    {
        // find out which way is right
        const FRotator Rotation = Controller->GetControlRotation();
        const FRotator YawRotation(0, Rotation.Yaw, 0);

        // get right vector 
        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        // add movement in that direction
        AddMovementInput(Direction, Value);
    }
}
