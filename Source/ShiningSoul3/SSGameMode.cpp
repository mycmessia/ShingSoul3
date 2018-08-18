// Fill out your copyright notice in the Description page of Project Settings.

#include "SSGameMode.h"
#include "SSCharacter.h"
#include "UObject/ConstructorHelpers.h"


ASSGameMode::ASSGameMode()
{
    // set default pawn class to our Blueprinted character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Characters/BP_SSCharacter"));
    if(PlayerPawnBPClass.Class != NULL)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
}
