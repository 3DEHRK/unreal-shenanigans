// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BRGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWinnerFound);

/**
 * 
 */
UCLASS()
class BATTLEROYALE_API ABRGameState : public AGameStateBase
{
	GENERATED_BODY()

public:

	UPROPERTY(ReplicatedUsing = OnRep_Winner, Transient, BlueprintReadOnly, Category = "Game State")
	class ABRPlayerState* Winner = nullptr;

	UFUNCTION()
	void OnRep_Winner();

	UPROPERTY(BlueprintAssignable, Category = "Game State")
	FWinnerFound OnWinnerFound;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
