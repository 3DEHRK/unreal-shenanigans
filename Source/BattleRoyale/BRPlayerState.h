// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "BRPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEROYALE_API ABRPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UPROPERTY(Transient, BlueprintReadOnly)
	float Health = 100.f;
	
};
