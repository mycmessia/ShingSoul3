// Fill out your copyright notice in the Description page of Project Settings.

#include "SSEventDispatcher.h"

FSSEventDispatcher::FSSEventDispatcher()
{
}


FSSEventDispatcher::~FSSEventDispatcher()
{
}

void FSSEventDispatcher::RegisterEvent(FString EventName, TFunction<void(void)> CallbackFunc)
{
	FSSEventBinding EventBinding;
	EventBinding.EventName = EventName;
	EventBinding.CallbackFunc = CallbackFunc;

	RegisteredEvents.Add(EventBinding);
}

void FSSEventDispatcher::FireEvent(FString EventName)
{
	for (FSSEventBinding& RegisteredEvent : RegisteredEvents)
	{
		if (RegisteredEvent.EventName == EventName)
		{
			RegisteredEvent.CallbackFunc();
		}
	}
}
