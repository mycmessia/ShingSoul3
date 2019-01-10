// Fill out your copyright notice in the Description page of Project Settings.

#include "CoreMinimal.h"

#pragma once

struct FSSEventBinding
{
	FString EventName;
	TFunction<void(void)> CallbackFunc;
};

/**
 * Event System used to decouple code
 *
 * Registering an event
 *
 * EventDispatcher.RegisterEvent("RegisterEventExample", []() {
 *		UE_LOG(LogTemp, Warning, TEXT("Registered Callback"));
 *	});
 *
 * Firing an event
 *
 * EventDispatcher.FireEvent("RegisterEventExample");
 */
struct SHININGSOUL3_API FSSEventDispatcher
{
public:
	FSSEventDispatcher();
	~FSSEventDispatcher();

	void RegisterEvent(FString EventName, TFunction<void(void)> CallbackFunc);
	void FireEvent(FString EventName);

private:
	TArray<FSSEventBinding> RegisteredEvents;
};

